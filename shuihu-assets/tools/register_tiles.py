"""Per-tile registration of generated atlases against the original 32x32 tile grid.

Generated atlases follow the source layout only approximately: cells drift by up to tens of pixels and rows are not
evenly spaced, so a uniform grid cut slices objects and drags slivers of neighbouring cells into a tile (the dark
seams in assembled maps). Here every non-empty source tile is located in the generated atlas by normalised
cross-correlation of blurred luminance and gradient magnitude around its expected position. Flat or ambiguous tiles
(cobblestone, water, grass) take the offset of confident neighbours. Output: data/tile-registration.json with one
crop box per tile; nothing is repainted and tile indices are unchanged.
Usage: python3 tools/register_tiles.py [bank-id ...]
"""
import json,sys
from pathlib import Path
import numpy as np
from PIL import Image,ImageFilter
from numpy.lib.stride_tricks import sliding_window_view

ROOT=Path(__file__).resolve().parents[1]/'dist'
STYLES=['pixel-hd','unreal','ghibli']
COARSE,SEARCH,FINE=4,14,4          # coarse factor, coarse search radius (coarse px), fine radius (full px)
MIN_STD,MIN_SCORE,MAX_JUMP=6.0,0.35,10.0

def features(im,blur):
  g=im.convert('L').filter(ImageFilter.GaussianBlur(blur));a=np.asarray(g,dtype=np.float32)
  gy,gx=np.gradient(a);return a,np.hypot(gx,gy)

def ncc(windows,template):
  t=template-template.mean();tn=np.sqrt((t*t).sum())
  if tn<1e-6:return np.zeros(windows.shape[:2],np.float32)
  w=windows-windows.mean(axis=(2,3),keepdims=True)
  return (w*t).sum(axis=(2,3))/(np.sqrt((w*w).sum(axis=(2,3)))*tn+1e-6)

def match(feats,tfeats,x,y,radius,size):
  """Best (dx,dy,score) of template features placed with top-left near (x,y) in feature images."""
  H,W=feats[0].shape;x0,y0=max(0,x-radius),max(0,y-radius);x1,y1=min(W,x+radius+size),min(H,y+radius+size)
  if x1-x0<size or y1-y0<size:return 0,0,-1.0
  score=sum(ncc(sliding_window_view(f[y0:y1,x0:x1],(size,size)),t) for f,t in zip(feats,tfeats))/len(feats)
  iy,ix=np.unravel_index(int(np.argmax(score)),score.shape)
  return x0+ix-x,y0+iy-y,float(score[iy,ix])

def register(source,generated,start_y):
  w,h=source.size;W,H=generated.size;cols,rows=w//32,h//32
  cell=W/cols                                   # full width is exact for every batch; rows carry the padding
  src=np.asarray(source.convert('RGB'));coarse_gen=features(generated.resize((round(W/COARSE),round(H/COARSE)),Image.Resampling.BOX),1.0)
  fine_gen=features(generated,2.0);csize=round(cell/COARSE);fsize=round(cell)
  tiles={}
  for row in range(rows):
    for col in range(cols):
      tile=source.crop((col*32,row*32,col*32+32,row*32+32))
      if src[row*32:row*32+32,col*32:col*32+32].max()<12:continue
      ex,ey=col*cell,start_y+row*cell
      ct=features(tile.resize((csize,csize),Image.Resampling.BICUBIC),1.0)
      dx,dy,_=match(coarse_gen,ct,round(ex/COARSE),round(ey/COARSE),SEARCH,csize)
      ft=features(tile.resize((fsize,fsize),Image.Resampling.BICUBIC),2.0)
      fx,fy,score=match(fine_gen,ft,round(ex)+dx*COARSE,round(ey)+dy*COARSE,FINE,fsize)
      tiles[(col,row)]={'offset':[dx*COARSE+fx+round(ex)-ex,dy*COARSE+fy+round(ey)-ey],'score':score,'std':float(np.asarray(tile.convert('L'),np.float32).std())}
  # Confident tiles keep their match unless it jumps away from its confident neighbours; the rest are interpolated.
  confident={k for k,v in tiles.items() if v['std']>=MIN_STD and v['score']>=MIN_SCORE}
  def neighbour_median(k,pool,radius):
    pts=[tiles[n]['offset'] for n in pool if n!=k and abs(n[0]-k[0])<=radius and abs(n[1]-k[1])<=radius]
    return np.median(np.array(pts),axis=0) if pts else None
  for k in sorted(confident):
    med=neighbour_median(k,confident,2)
    if med is not None and np.hypot(*(np.array(tiles[k]['offset'])-med))>MAX_JUMP and tiles[k]['score']<.7:tiles[k]['outlier']=True
  confident={k for k in confident if not tiles[k].get('outlier')}
  fallback=np.median(np.array([tiles[k]['offset'] for k in confident]),axis=0) if confident else np.zeros(2)
  out={};offsets={}
  for k,v in tiles.items():
    if k in confident:method,off='matched',np.array(v['offset'],float)
    else:
      off=None
      for radius in (1,2,3,16):
        off=neighbour_median(k,confident,radius)
        if off is not None:break
      method,off='neighbour-interpolated',(off if off is not None else fallback)
    col,row=k;x=col*cell+off[0];y=start_y+row*cell+off[1];offsets[k]=off
    out[col+row*cols]={'box':[round(x),round(y),round(x+cell),round(y+cell)],'method':method,'score':round(v['score'],3)}
  # Shared corners (replaced by refine() boxes when that runs): each grid corner takes the mean offset of the tiles touching it, and every tile is cut as the quad
  # of its four corners. Tiles that touch in the atlas then share their cut line exactly, so multi-tile objects stay
  # continuous wherever the map repeats the atlas neighbourhood.
  def corner(c,r):
    near=[offsets[n] for n in ((c-1,r-1),(c,r-1),(c-1,r),(c,r)) if n in offsets]
    o=np.mean(np.array(near),axis=0);return [round(float(c*cell+o[0]),2),round(float(start_y+r*cell+o[1]),2)]
  for (col,row) in offsets:
    out[col+row*cols]['quad']=corner(col,row)+corner(col,row+1)+corner(col+1,row+1)+corner(col+1,row)
  return {'cell':cell,'startY':start_y,'tiles':out,'matched':len(confident),'total':len(tiles)}

def refine(result,source,generated,counts,radius=8,prior=1.0,rounds=6):
  """Shift each tile's cut by up to `radius` px so structure lines continue across the seams the maps use.

  Registration places each tile where it best resembles its source, but the generator draws a pillar or wall line at
  slightly different positions in different cells, so two tiles that the map stacks can still step at the seam.
  For every map adjacency that is continuous in the original, the cost is the mean absolute difference between the
  touching edge pixels; a prior of `prior` per pixel of displacement keeps tiles near their registered position.
  Iterated conditional modes over integer offsets; returns translated boxes (quad = box corners)."""
  from tile_seams import _continuous
  W,H=generated.size;img=np.asarray(generated,dtype=np.float32);cols=source.size[0]//32;c=round(result['cell'])
  src=np.asarray(source);tiles=result['tiles']
  originals={int(t):src[int(t)//cols*32:int(t)//cols*32+32,int(t)%cols*32:int(t)%cols*32+32] for t in tiles}
  base={int(t):(v['box'][0],v['box'][1]) for t,v in tiles.items()}
  pairs=[(a,b,axis,np.log1p(n)) for (axis,a,b),n in counts.items() if a in base and b in base and a!=b and _continuous(originals,a,b,axis)]
  shift={t:(0,0) for t in base};R=range(-radius,radius+1)
  def edge(t,side,dx,dy):
    x,y=base[t][0]+dx,base[t][1]+dy
    if x<0 or y<0 or x+c>W or y+c>H:return None
    return {'L':img[y:y+c,x],'R':img[y:y+c,x+c-1],'U':img[y,x:x+c],'D':img[y+c-1,x:x+c]}[side]
  touching={t:[] for t in base}
  for a,b,axis,w in pairs:
    touching[a].append((b,'R' if axis=='x' else 'D','L' if axis=='x' else 'U',w));touching[b].append((a,'L' if axis=='x' else 'U','R' if axis=='x' else 'D',w))
  for _ in range(rounds):
    moved=0
    for t in base:
      if not touching[t]:continue
      fixed=[(edge(n,other,*shift[n]),side,w) for n,side,other,w in touching[t]]
      best,choice=None,shift[t]
      for dx in R:
        for dy in R:
          cost=prior*(abs(dx)+abs(dy));total=0
          for e,side,w in fixed:
            mine=edge(t,side,dx,dy)
            if e is None or mine is None:cost=None;break
            cost+=w*float(np.abs(mine-e).mean());total+=w
          if cost is None:continue
          if best is None or cost<best:best,choice=cost,(dx,dy)
      if choice!=shift[t]:shift[t]=choice;moved+=1
    if not moved:break
  for t,v in tiles.items():
    dx,dy=shift[int(t)];x1,y1,x2,y2=v['box'];x1,x2,y1,y2=x1+dx,x2+dx,y1+dy,y2+dy
    v['box']=[x1,y1,x2,y2];v['quad']=[x1,y1,x1,y2,x2,y2,x2,y1];v['seamShift']=[dx,dy]
  result['refinedPairs']=len(pairs);return result

if __name__=='__main__':
  from tile_seams import adjacency
  rules=json.loads((ROOT/'data/tile-rules.json').read_text())
  catalog=json.loads((ROOT/'data/catalog.json').read_text());old=json.loads((ROOT/'data/atlas-registration.json').read_text())
  banks=[i for i in catalog['items'] if i['category']=='map-banks' and (len(sys.argv)<2 or i['id'] in sys.argv[1:])]
  path=ROOT/'data/tile-registration.json';data=json.loads(path.read_text()) if path.exists() else {}
  for bank in banks:
    for style in STYLES:
      files=list((ROOT/'production').glob(f"batch-*/{bank['id']}-{style}.png"))
      if len(files)!=1:continue
      source=Image.open(ROOT/bank['image']).convert('RGB');generated=Image.open(files[0]).convert('RGB')
      start=old.get(f"{bank['id']}-{style}",{}).get('y',0.0)
      r=refine(register(source,generated,start),source,generated,adjacency(rules,bank['id']));r['image']=str(files[0].relative_to(ROOT));r['status']='per-tile-registration-needs-visual-review'
      data[f"{bank['id']}-{style}"]=r;print(bank['id'],style,f"{r['matched']}/{r['total']} matched",flush=True)
  path.write_text(json.dumps(data,indent=1))
