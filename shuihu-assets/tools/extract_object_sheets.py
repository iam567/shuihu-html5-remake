"""Cut generated object sheets (prepare_object_sheets.py) back into 128x128 tiles.

Each piece keeps its reference position on the sheet; every tile the piece draws is located near its expected cell
by the same luminance/gradient correlation as register_tiles.py (search radius RADIUS px), so a few pixels of
generator drift do not drag a neighbour's edge into the tile. Writes generated/object-tiles/<bank>-<style>/<t>.png
and data/object-tile-overrides.json, which assemble_generated_maps.py prefers over atlas cuts.
Usage: python3 tools/extract_object_sheets.py production/batch-006-pilot [more batch dirs]
"""
import json,sys
from pathlib import Path
from PIL import Image
import numpy as np
from register_tiles import features,match
from tile_seams import adjacency

def ground_mask(cell,samples,tolerance=22.0):
  """Pixels of a generated tile that look like the piece's own generated ground and reach the tile border."""
  a=np.asarray(cell,np.float32);flat=a.reshape(-1,3)
  d=np.min(np.stack([np.abs(flat-s).sum(axis=1) for s in samples]),axis=0).reshape(a.shape[:2])/3
  near=d<tolerance;h,w=near.shape;mask=np.zeros_like(near)
  stack=[(y,x) for y in range(h) for x in range(w) if (y in(0,h-1) or x in(0,w-1)) and near[y,x]]
  for y,x in stack:mask[y,x]=True
  while stack:
    y,x=stack.pop()
    for ny,nx in((y+1,x),(y-1,x),(y,x+1),(y,x-1)):
      if 0<=ny<h and 0<=nx<w and near[ny,nx] and not mask[ny,nx]:mask[ny,nx]=True;stack.append((ny,nx))
  return mask

ROOT=Path(__file__).resolve().parents[1];DIST=ROOT/'dist';CELL,RADIUS=128,12
rules=json.loads((DIST/'data/tile-rules.json').read_text());catalog=json.loads((DIST/'data/catalog.json').read_text());banks={i['id']:i for i in catalog['items'] if i['category']=='map-banks'}
index_path=DIST/'data/object-tile-overrides.json';index=json.loads(index_path.read_text()) if index_path.exists() else {}
for batch in map(Path,sys.argv[1:]):
  pieces=json.loads((batch/'pieces.json').read_text())
  for job in json.loads((batch/'jobs.json').read_text()):
    out=batch/(job['id']+'.png')
    if not out.exists():print('missing',out.name);continue
    ref=Image.open(batch/job['reference']).convert('RGB');gen=Image.open(out).convert('RGB')
    if gen.size!=ref.size:gen=gen.resize(ref.size,Image.Resampling.LANCZOS)
    feats=features(gen,2.0);mine=[p for p in pieces if p['sheet']==job['sheet']]
    # A sheet holds pieces of one bank (sourceId) or, for --small batches, of several banks (each piece's bankId).
    bank_of=lambda p:p.get('bankId') or job['sourceId'];info={}
    for b in {bank_of(p) for p in mine}:
      src=Image.open(DIST/banks[b]['image']).convert('RGB');counts=adjacency(rules,b)
      folder=DIST/'generated/object-tiles'/f"{b}-{job['style']}";folder.mkdir(parents=True,exist_ok=True)
      info[b]={'src':src,'cols':src.width//32,'folder':folder,'ground':{t for (a,t,c),n in counts.items() if a=='x' and t==c and counts[('y',t,t)]}}
    # Colour samples of generated ground: every pure ground cell of the bank's pieces on this sheet (all pieces when
    # the bank has none here), reduced to 24 colours.
    def ground_samples(cells):
      if not cells:return []
      strip=Image.new('RGB',(CELL*len(cells),CELL));[strip.paste(c,(k*CELL,0)) for k,c in enumerate(cells)]
      return [np.array(rgb,np.float32) for _,rgb in strip.quantize(24).convert('RGB').getcolors(1<<16)]
    ground_cells=lambda ps:[gen.crop((p['box'][0]+i*CELL,p['box'][1]+j*CELL,p['box'][0]+i*CELL+CELL,p['box'][1]+j*CELL+CELL))
      for p in ps for j,row in enumerate(p['context']) for i,t in enumerate(row) if t in info[bank_of(p)]['ground']]
    sheet_samples=ground_samples(ground_cells(mine))
    for b in info:info[b]['samples']=ground_samples(ground_cells([p for p in mine if bank_of(p)==b])) or sheet_samples
    for p in mine:
      x0,y0=p['box'][:2];b=bank_of(p);src,cols,folder,samples=(info[b][k] for k in ('src','cols','folder','samples'))
      for j,row in enumerate(p['layout']):
        for i,t in enumerate(row):
          if t not in p['draws']:continue
          tile=src.crop((t%cols*32,t//cols*32,t%cols*32+32,t//cols*32+32)).resize((CELL,CELL),Image.Resampling.BICUBIC)
          ex,ey=x0+i*CELL,y0+j*CELL;dx,dy,score=match(feats,features(tile,2.0),ex,ey,RADIUS,CELL)
          # Inside a whole-object piece neighbours were drawn together, so stay on the reference grid unless the match is sure.
          if score<.5:dx,dy=0,0
          cut=gen.crop((ex+dx,ey+dy,ex+dx+CELL,ey+dy+CELL))
          # Magenta from the sheet gutter bleeds a few pixels into fragment borders; take the next pixel inward.
          a=np.asarray(cut).astype(np.int16).copy();L=p["layout"];band=8
          spill=(a[...,0]>a[...,1]+15)&(a[...,2]>a[...,1]+15)
          for side,(jj,ii) in {'L':(j,i-1),'R':(j,i+1),'U':(j-1,i),'D':(j+1,i)}.items():
            if 0<=jj<len(L) and 0<=ii<len(L[0]) and L[jj][ii]>=0:continue
            for k in range(band-1,-1,-1):
              if side=='L':sel=spill[:,k];a[sel,k]=a[sel,k+1]
              if side=='R':sel=spill[:,-1-k];a[sel,-1-k]=a[sel,-2-k]
              if side=='U':sel=spill[k];a[k,sel]=a[k+1,sel]
              if side=='D':sel=spill[-1-k];a[-1-k,sel]=a[-2-k,sel]
          cut=Image.fromarray(a.astype(np.uint8));cut.save(folder/f'{t}.png');mask=None
          if samples:
            m=ground_mask(cut,samples)
            # Sides on the piece border touch the magenta gutter in the sheet and pick up a tinted fringe; mark that
            # 4 px band as ground too (inherit_ground still limits replacement to where the original is ground).
            L=p['layout'];outside=lambda jj,ii:not(0<=jj<len(L) and 0<=ii<len(L[0])) or L[jj][ii]<0
            if outside(j,i-1):m[:,:4]=True
            if outside(j,i+1):m[:,-4:]=True
            if outside(j-1,i):m[:4,:]=True
            if outside(j+1,i):m[-4:,:]=True
            if .03<m.mean()<.9:Image.fromarray((m*255).astype(np.uint8)).save(folder/f'{t}-ground.png');mask=str((folder/f'{t}-ground.png').relative_to(DIST))
          index.setdefault(f"{b}-{job['style']}",{})[str(t)]={'image':str((folder/f'{t}.png').relative_to(DIST)),'groundMask':mask,'sheet':job['id'],'shift':[int(dx),int(dy)],'score':round(score,3),'status':'object-sheet-awaiting-review'}
    print('cut',job['id'])
index_path.write_text(json.dumps(index,indent=1))
