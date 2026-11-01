"""Make repeated ground tiles (grass, cobblestone, water, dirt) join without seams, as the original tiles do.

The original ground tiles are drawn to tile: a tile placed next to itself, or next to a variant that shares its edge
pixels, shows no seam. Generated tiles do not. For every bank and style:
  1. Ground anchors: tiles the maps place next to themselves both left-right and top-bottom (grass, cobblestone,
     water, dirt fields). Each is made wrap-tileable: roll by half a tile so the seam moves to the middle, cover it
     with the best-matching strip taken from the same tile, and join both sides along minimum-difference cuts.
     Tiles repeated along one axis only (walls, fences, eaves, stacked crates) are objects and are never rolled.
  2. Variants: a tile whose original edge pixels equal a ground anchor's original edge on the same side takes that
     anchor's generated edge band, joined to its own interior along a minimum-difference cut. Two tiles that share
     an edge in the original then share it in the generated set as well.
  3. Colour steps: for every adjacency the maps use where the original is continuous across the seam, both tiles get
     a smooth additive correction that fades out over the edge band, so neighbouring edges meet at the same colour.
     Shapes are not moved, only shading.
Tile indices, sizes and positions never change.
"""
import numpy as np
from collections import Counter

SIZE,BAND,STRIP,OVERLAP=128,20,28,14
EDGE_MATCH=8.0     # mean abs RGB difference of the 4 original edge pixels to count as the same edge

def _cut_path(cost):
  """Minimum-cost top-to-bottom path through cost (rows x cols); returns column index per row."""
  h,w=cost.shape;acc=cost.copy();back=np.zeros((h,w),np.int16)
  for y in range(1,h):
    left=np.r_[np.inf,acc[y-1,:-1]];right=np.r_[acc[y-1,1:],np.inf];stack=np.vstack([left,acc[y-1],right])
    k=np.argmin(stack,axis=0);back[y]=k-1;acc[y]+=stack[k,np.arange(w)]
  path=np.zeros(h,np.int32);path[-1]=int(np.argmin(acc[-1]))
  for y in range(h-1,0,-1):path[y-1]=min(w-1,max(0,path[y]+back[y,path[y]]))
  return path

def _join(base,patch,x0,width,keep_left):
  """Copy patch columns [x0,x0+width) over base, entering/leaving along a min-cut inside the overlap zones."""
  out=base.copy();diff=np.abs(base.astype(np.float32)-patch.astype(np.float32)).sum(axis=2)
  lo=x0;left=_cut_path(diff[:,lo:lo+OVERLAP])+lo if keep_left else np.full(base.shape[0],x0)
  hi=x0+width-OVERLAP;right=_cut_path(diff[:,hi:hi+OVERLAP])+hi
  for y in range(base.shape[0]):out[y,left[y]:right[y]]=patch[y,left[y]:right[y]]
  return out

def tileable_x(tile):
  """Wrap-tileable along x: the left and right edges continue each other."""
  rolled=np.roll(tile,SIZE//2,axis=1);width=STRIP+2*OVERLAP;x0=SIZE//2-width//2
  left=rolled[:,x0:x0+OVERLAP].astype(np.float32);right=rolled[:,x0+width-OVERLAP:x0+width].astype(np.float32)
  best,where=None,0
  for sx in range(0,SIZE-width+1):
    cand=tile[:,sx:sx+width].astype(np.float32)
    cost=np.abs(cand[:,:OVERLAP]-left).sum()+np.abs(cand[:,-OVERLAP:]-right).sum()
    if best is None or cost<best:best,where=cost,sx
  patch=rolled.copy();patch[:,x0:x0+width]=tile[:,where:where+width]
  return _join(rolled,patch,x0,width,True)

def tileable_y(tile):return tileable_x(tile.transpose(1,0,2)).transpose(1,0,2)

def _edge(orig,side):
  return {'L':orig[:,:4],'R':orig[:,-4:],'U':orig[:4,:],'D':orig[-4:,:]}[side].astype(np.float32)

def _put_band(tile,source,side):
  """Replace one edge band of tile with source's band, joined inward along a min-cut."""
  t,s=tile,source
  if side in 'UD':t,s=t.transpose(1,0,2),s.transpose(1,0,2)
  if side in 'RD':t,s=t[:,::-1],s[:,::-1]
  patch=t.copy();patch[:,:BAND+OVERLAP]=s[:,:BAND+OVERLAP]
  diff=np.abs(t.astype(np.float32)-s.astype(np.float32)).sum(axis=2);cut=_cut_path(diff[:,BAND:BAND+OVERLAP])+BAND
  out=t.copy()
  for y in range(out.shape[0]):out[y,:cut[y]]=s[y,:cut[y]]
  if side in 'RD':out=out[:,::-1]
  if side in 'UD':out=out.transpose(1,0,2)
  return out

def adjacency(rules,bank_id):
  counts=Counter()
  for m in rules['maps'].values():
    if m['bankId']!=bank_id:continue
    g,w=m['graphics'],m['width']
    for i,t in enumerate(g):
      if (i+1)%w and i+1<len(g):counts[('x',t,g[i+1])]+=1
      if i+w<len(g):counts[('y',t,g[i+w])]+=1
  return counts

def seamless(tiles,originals,counts,ground_masks=None):
  """tiles/originals: {index: HxWx3 uint8}; ground_masks: {index: 128x128 bool} marking generated ground in tiles
  redrawn as whole objects. Returns (new tiles, report)."""
  out={k:v.copy() for k,v in tiles.items()};report={'anchors':{},'variants':[]}
  ground=[t for t in tiles if counts[('x',t,t)] and counts[('y',t,t)]]
  anchors={'x':ground,'y':ground}
  for t in ground:out[t]=tileable_y(tileable_x(out[t]));report['anchors'][t]=['x','y']
  inherit_ground(out,originals,ground,report,ground_masks or {})
  # Most-used anchor first, so a variant follows the edge the maps show most.
  order={axis:sorted(ts,key=lambda t:-counts[(axis,t,t)]) for axis,ts in anchors.items()}
  inherited={i[0] for i in report['inherited']}
  for t in tiles:
    # Inherited tiles already carry the anchor's ground at their edges; a forced band would slice flowers or tufts.
    if t in inherited:continue
    for side,axis in (('L','x'),('R','x'),('U','y'),('D','y')):
      if t in anchors[axis]:continue
      for a in order[axis]:
        if np.abs(_edge(originals[t],side)-_edge(originals[a],side)).mean()<=EDGE_MATCH:
          out[t]=_put_band(out[t],out[a],side);report['variants'].append([t,side,a]);break
  out,report['colourSteps']=colour_steps(out,originals,counts)
  return out,report

def _continuous(originals,a,b,axis):
  """Original pixels run on across the a|b seam about as smoothly as inside the tiles."""
  A,B=originals[a].astype(np.float32),originals[b].astype(np.float32)
  if axis=='y':A,B=A.transpose(1,0,2),B.transpose(1,0,2)
  seam=np.abs(A[:,-1]-B[:,0]).mean();inside=(np.abs(np.diff(A,axis=1)).mean()+np.abs(np.diff(B,axis=1)).mean())/2
  return seam<=1.5*inside+4

def _smooth(v,radius=6):
  k=np.ones(2*radius+1,np.float32)/(2*radius+1);pad=np.pad(v,((radius,radius),(0,0)),mode='edge')
  return np.stack([np.convolve(pad[:,c],k,mode='valid') for c in range(v.shape[1])],axis=1)

def colour_steps(tiles,originals,counts):
  """Average each tile edge towards the edges it meets; returns adjusted tiles and the number of corrected sides."""
  targets={};weights={}
  for (axis,a,b),n in counts.items():
    if a not in tiles or b not in tiles or not _continuous(originals,a,b,axis):continue
    A,B=tiles[a].astype(np.float32),tiles[b].astype(np.float32)
    ea,eb=(A[:,-1],B[:,0]) if axis=='x' else (A[-1],B[0])
    mid=(ea+eb)/2
    for key,own in (((a,'R' if axis=='x' else 'D'),ea),((b,'L' if axis=='x' else 'U'),eb)):
      targets[key]=targets.get(key,0)+n*(mid-own);weights[key]=weights.get(key,0)+n
  out={k:v.astype(np.float32) for k,v in tiles.items()};ramp=np.linspace(1,0,BAND,dtype=np.float32)
  for (t,side),total in targets.items():
    delta=_smooth(total/weights[(t,side)])
    if side=='L':out[t][:,:BAND]+=delta[:,None,:]*ramp[None,:,None]
    if side=='R':out[t][:,-BAND:]+=delta[:,None,:]*ramp[::-1][None,:,None]
    if side=='U':out[t][:BAND]+=ramp[:,None,None]*delta[None,:,:]
    if side=='D':out[t][-BAND:]+=ramp[::-1][:,None,None]*delta[None,:,:]
  return {k:np.clip(v,0,255).astype(np.uint8) for k,v in out.items()},len(targets)

def _blur_mask(mask,radius):
  from PIL import Image,ImageFilter
  return np.asarray(Image.fromarray((mask*255).astype(np.uint8)).filter(ImageFilter.GaussianBlur(radius)),np.float32)/255

def inherit_ground(tiles,originals,ground,report,ground_masks,protect=8,feather=4,min_share=.12):
  """Objects drawn on ground (trees, wells, crates): where the original pixels equal a ground anchor's pixels at the
  same position, the generated tile takes that anchor's generated ground, so its background matches the field around
  it. The shared region is shrunk by `protect` px to leave room for the generated object outline, then feathered."""
  from PIL import Image,ImageFilter
  report['inherited']=[]
  for t in list(tiles):
    if t in ground:continue
    best,share=None,0
    for a in ground:
      m=(np.abs(originals[t].astype(np.int16)-originals[a].astype(np.int16)).max(axis=2)<=6)|_palette_ground(originals[t],originals[a])
      if m.mean()>share:best,share=(a,m),m.mean()
    if best is None or share<min_share or share>.98:continue
    a,m=best
    if t in ground_masks:
      # Whole-object redraw: the generated ground itself was segmented, so only a thin margin is needed.
      # Only near the original ground: the generated object may be drawn smaller than the original silhouette, but a
      # trunk or canopy centre whose colours resemble the ground must never be replaced.
      near=np.asarray(Image.fromarray((m*255).astype(np.uint8)).resize((SIZE,SIZE),Image.Resampling.NEAREST).filter(ImageFilter.MaxFilter(33)))>127
      big=Image.fromarray(((ground_masks[t]&near)*255).astype(np.uint8)).filter(ImageFilter.MinFilter(5))
      alpha=_blur_mask(np.asarray(big,np.float32)/255,2)[...,None]
      tiles[t]=(alpha*tiles[a].astype(np.float32)+(1-alpha)*tiles[t].astype(np.float32)).astype(np.uint8)
      report['inherited'].append([t,a,round(float(ground_masks[t].mean()),2)]);continue
    big=Image.fromarray((m*255).astype(np.uint8)).resize((SIZE,SIZE),Image.Resampling.NEAREST).filter(ImageFilter.MinFilter(2*protect+1))
    alpha=_blur_mask(np.asarray(big,np.float32)/255,feather)[...,None]
    tiles[t]=(alpha*tiles[a].astype(np.float32)+(1-alpha)*tiles[t].astype(np.float32)).astype(np.uint8)
    report['inherited'].append([t,a,round(float(share),2)])

def _components(mask):
  """Number of 4-connected True regions in a small boolean mask."""
  seen=np.zeros_like(mask);count=0;h,w=mask.shape
  for y in range(h):
    for x in range(w):
      if mask[y,x] and not seen[y,x]:
        count+=1;stack=[(y,x)];seen[y,x]=True
        while stack:
          cy,cx=stack.pop()
          for ny,nx in((cy+1,cx),(cy-1,cx),(cy,cx+1),(cy,cx-1)):
            if 0<=ny<h and 0<=nx<w and mask[ny,nx] and not seen[ny,nx]:seen[ny,nx]=True;stack.append((ny,nx))
  return count

def _palette_ground(orig,anchor,max_object_parts=6):
  """Ground drawn with the anchor's colours but not its exact pattern (a tree's own cobblestones): pixels in the
  anchor palette that connect to the tile border. Rejected when the remaining object breaks into many fragments,
  which means the tile is a ground variant such as a shadowed field rather than an object on ground."""
  palette={tuple(c) for c in anchor.reshape(-1,3)};h,w=orig.shape[:2]
  inpal=np.array([[tuple(orig[y,x]) in palette for x in range(w)] for y in range(h)])
  mask=np.zeros((h,w),bool);stack=[(y,x) for y in range(h) for x in range(w) if (y in(0,h-1) or x in(0,w-1)) and inpal[y,x]]
  for y,x in stack:mask[y,x]=True
  while stack:
    y,x=stack.pop()
    for ny,nx in((y+1,x),(y-1,x),(y,x+1),(y,x-1)):
      if 0<=ny<h and 0<=nx<w and inpal[ny,nx] and not mask[ny,nx]:mask[ny,nx]=True;stack.append((ny,nx))
  if not mask.any() or _components(~mask)>max_object_parts:return np.zeros((h,w),bool)
  return mask
