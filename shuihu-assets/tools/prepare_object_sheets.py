"""Reference sheets that show multi-tile objects whole, so the generator redraws each object as one picture.

Input: data/object-groups.json (find_object_groups.py). For every bank, groups are chosen greedily until every tile
that sits in an object with scattered atlas seams is covered once; groups larger than MAX x MAX cells are split into
windows. Each piece is the original map region (all cells of its bounding box, so ground context is included) at 4x
nearest-neighbour. Pieces are shelf-packed onto 1536x1024 sheets separated by pure magenta gutters.
Writes production/batch-006/{sheet pngs, prompts, jobs.json, pieces.json}. Nothing is submitted.
With --small only objects that fit in SMALL x SMALL cells (trees, bushes, wells, barrels) are drawn, tiles that
already have an object-sheet override are skipped, and pieces of all banks share sheets (production/objects-small-1).
Usage: python3 tools/prepare_object_sheets.py [--small]
"""
import json,sys
from pathlib import Path
from PIL import Image

ROOT=Path(__file__).resolve().parents[1];DIST=ROOT/'dist';OUT=ROOT/'production/batch-006'
SHEET_W,SHEET_H,GUTTER,CELL,MAX,SMALL=1536,1024,32,128,6,3
SMALL_MODE='--small' in sys.argv
if SMALL_MODE:OUT=ROOT/'production/objects-small-1'
STYLES={'pixel-hd':'modern crisp JRPG pixel art, clean readable clustered shading',
        'unreal':'stylized realistic PBR game textures with neutral flat lighting',
        'ghibli':'warm hand-painted animation background art, Ghibli inspired'}

def pieces_for_bank(groups,rules,skip=frozenset()):
  need=[g for g in groups if g['scatteredSeams']];uncovered={t for g in need for t in g['tiles']}-skip;pieces=[]
  def windows(g):
    L=g['layout'];H,W=len(L),len(L[0])
    for y in range(0,H,MAX):
      for x in range(0,W,MAX):
        sub=[row[x:x+MAX] for row in L[y:y+MAX]]
        if any(t>=0 for r in sub for t in r):yield sub,g['maps'][0]['mapId'],g['maps'][0]['x']+x,g['maps'][0]['y']+y
  candidates=[w+(g['id'],g['uses']) for g in need for w in windows(g)]
  while uncovered:
    def gain(c):return len({t for r in c[0] for t in r if t in uncovered})
    best=max(candidates,key=lambda c:(gain(c)/sum(t>=0 for r in c[0] for t in r),c[5],gain(c)))
    if not gain(best):break
    sub,map_id,x,y,gid,_=best;m=rules['maps'][map_id]
    full=[[m['graphics'][(y+j)*m['width']+x+i] for i in range(len(sub[0]))] for j in range(len(sub))]
    pieces.append({'group':gid,'mapId':map_id,'x':x,'y':y,'layout':sub,'context':full,'draws':sorted({t for r in sub for t in r if t in uncovered})})
    uncovered-={t for r in sub for t in r};candidates.remove(best)
  return pieces

def pack(pieces):
  """Shelf packing, tallest first; returns [(sheet, x, y)] aligned with pieces."""
  order=sorted(range(len(pieces)),key=lambda i:(-len(pieces[i]['layout']),-len(pieces[i]['layout'][0])))
  place=[None]*len(pieces);sheets=[]
  for i in order:
    w,h=len(pieces[i]['layout'][0])*CELL,len(pieces[i]['layout'])*CELL;done=False
    for s,shelves in enumerate(sheets):
      for shelf in shelves:
        if shelf['h']>=h and shelf['x']+w+GUTTER<=SHEET_W:place[i]=(s,shelf['x'],shelf['y']);shelf['x']+=w+GUTTER;done=True;break
      if done:break
      top=shelves[-1]['y']+shelves[-1]['h']+GUTTER
      if top+h+GUTTER<=SHEET_H:shelves.append({'y':top,'h':h,'x':GUTTER+w+GUTTER});place[i]=(s,GUTTER,top);done=True;break
    if not done:sheets.append([{'y':GUTTER,'h':h,'x':GUTTER+w+GUTTER}]);place[i]=(len(sheets)-1,GUTTER,GUTTER)
  return place,len(sheets)

if __name__=='__main__':
  rules=json.loads((DIST/'data/tile-rules.json').read_text());catalog=json.loads((DIST/'data/catalog.json').read_text())
  groups=json.loads((DIST/'data/object-groups.json').read_text())['groups'];banks={i['id']:i for i in catalog['items'] if i['category']=='map-banks'}
  if SMALL_MODE:groups=[g for g in groups if len(g['layout'])<=SMALL and len(g['layout'][0])<=SMALL]
  index_path=DIST/'data/object-tile-overrides.json';index=json.loads(index_path.read_text()) if index_path.exists() and SMALL_MODE else {}
  OUT.mkdir(parents=True,exist_ok=True);all_pieces=[];jobs=[];pools={}
  for bank_id in banks:
    skip=frozenset.intersection(*(frozenset(map(int,index.get(f'{bank_id}-{s}',{}))) for s in STYLES))
    pieces=pieces_for_bank([g for g in groups if g['bankId']==bank_id],rules,skip)
    for p in pieces:p['bankId']=bank_id
    if pieces:pools.setdefault('all' if SMALL_MODE else bank_id,[]).extend(pieces)
  sources={b:Image.open(DIST/banks[b]['image']).convert('RGB') for b in {p['bankId'] for ps in pools.values() for p in ps}}
  for pool,pieces in pools.items():
    place,n=pack(pieces);images=[Image.new('RGB',(SHEET_W,SHEET_H),(255,0,255)) for _ in range(n)]
    prefix='objects-small' if SMALL_MODE else f'objects-{pool}'
    for p,(s,x,y) in zip(pieces,place):
      src=sources[p['bankId']];cols=src.width//32
      for j,row in enumerate(p['context']):
        for i,t in enumerate(row):
          images[s].paste(src.crop((t%cols*32,t//cols*32,t%cols*32+32,t//cols*32+32)).resize((CELL,CELL),Image.Resampling.NEAREST),(x+i*CELL,y+j*CELL))
      p.update(sheet=f'{prefix}-{s+1}',box=[x,y,x+len(p['layout'][0])*CELL,y+len(p['layout'])*CELL]);all_pieces.append(p)
    for s,im in enumerate(images):
      name=f'{prefix}-{s+1}';im.save(OUT/f'{name}-reference.png')
      for style,desc in STYLES.items():
        prompt=(f'Use case: style-transfer. Edit target: supplied sheet of retro game map fragments on a flat magenta background. '
          f'Redraw every fragment in {desc}. Each fragment is one scene: trees, houses, walls, bridges and their surrounding ground must be '
          'drawn as single continuous objects, so a tree is one whole tree and a building is one whole building, with outlines, roof lines, '
          'pillars and trunks continuing straight across the whole fragment. Keep every fragment exactly where it is, at exactly the same size, '
          'with the same outline, layout, object positions, doors, windows, stairs and colours as the reference; the fragment edges stay sharp '
          'straight rectangles. Ground between objects (grass, cobblestone, water, dirt) keeps the same material and fills to the fragment edge. '
          'The magenta background stays flat pure #ff00ff and never becomes scenery. No text, letters, signs with writing, borders, frames, '
          'vignettes, drop shadows outside fragments, grid lines or labels. Same canvas size and aspect ratio as the reference.')
        (OUT/f'{name}-{style}.txt').write_text(prompt)
        jobs.append({'id':f'{name}-{style}','kind':'object-sheet','style':style,'reference':f'{name}-reference.png','size':'1536x1024','sourceId':None if SMALL_MODE else pool,'sheet':name})
  (OUT/'jobs.json').write_text(json.dumps(jobs,indent=2));(OUT/'pieces.json').write_text(json.dumps(all_pieces))
  print(json.dumps({'sheets':len(jobs)//len(STYLES),'jobs':len(jobs),'pieces':len(all_pieces),'banks':len(sources),'tilesRedrawn':sum(len(p['draws']) for p in all_pieces)}))
