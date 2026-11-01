"""Pull whole-map redraws back onto the original cell grid.

The generator keeps the layout but drifts: a slight global scale/shift plus local wobble of up to a third of a cell.
Per cell, check_whole_maps.check() finds where the original's content landed in the redraw. A robust affine fit of
those offsets (cells off by more than OUTLIER px from the fit are dropped and the fit repeated) takes out the global
part; the remaining per-cell residuals of trusted cells are spread to the other cells by diffusion, smoothed, and
the redraw is resampled through the resulting smooth displacement field (bilinear, edge-clamped). Drift can exceed
the check's search radius, so ROUNDS measure again on the corrected picture with shrinking radii; the fields are
added and the untouched redraw is resampled once. Only geometry changes. Writes production/<batch>/aligned/<job>.png and aligned.json (offsets before/after); check, publish and
finalize scripts prefer aligned/ images. Untouched originals stay as production/<batch>/<job>.png.
Usage: python3 tools/align_whole_maps.py BATCH [JOBID ...]
"""
import json,sys
from pathlib import Path
from PIL import Image
import numpy as np
from check_whole_maps import check,DIST,ROOT,MIN_SCORE

OUTLIER,SMOOTH_ROUNDS,DIFFUSE_ROUNDS,ROUNDS=8,2,200,(24,12,8)
# Local residual warping bent walls and floor lines ("gravity well" look), so only the global affine part is applied:
# straight lines stay straight. Maps an affine fix cannot align fail the check and fall back / get regenerated.
AFFINE_ONLY=True

def field(cells,w,h):
  """Displacement (dx,dy) per cell in original 32 px units: where to sample the redraw for each cell centre."""
  good=[c for c in cells if c['score']>=MIN_SCORE]
  if len(good)<6:return np.zeros((h,w,2))
  X=np.array([[c['x']+.5,c['y']+.5,1] for c in good]);D=np.array([[c['dx'],c['dy']] for c in good],float);keep=np.ones(len(good),bool)
  for _ in range(3):
    A=np.linalg.lstsq(X[keep],D[keep],rcond=None)[0];keep=np.abs(D-X@A).max(axis=1)<=OUTLIER
    if keep.sum()<6:keep[:]=True;break
  gy,gx=np.mgrid[0:h,0:w];base=np.stack([gx+.5,gy+.5,np.ones_like(gx)],-1)@A
  if AFFINE_ONLY:return base
  res=np.zeros((h,w,2));known=np.zeros((h,w),bool)
  for c,k,d in zip(good,keep,D-X@A):
    if k:res[c['y'],c['x']]=d;known[c['y'],c['x']]=True
  fill=res.copy()
  for _ in range(DIFFUSE_ROUNDS):
    p=np.pad(fill,((1,1),(1,1),(0,0)),mode='edge');avg=(p[:-2,1:-1]+p[2:,1:-1]+p[1:-1,:-2]+p[1:-1,2:])/4
    fill=np.where(known[...,None],res,avg)
  for _ in range(SMOOTH_ROUNDS):
    p=np.pad(fill,((1,1),(1,1),(0,0)),mode='edge');fill=(4*fill+p[:-2,1:-1]+p[2:,1:-1]+p[1:-1,:-2]+p[1:-1,2:])/8
  return base+fill

def warp(gen,disp,w,h):
  """Resample gen so that original cell (x,y) shows gen content displaced by disp (32 px units)."""
  W,H=gen.size;k=W/(w*32);a=np.asarray(gen,np.float32)
  # Displacement at every output pixel: bilinear between cell centres.
  ys=(np.arange(H)+.5)/(32*k)-.5;xs=(np.arange(W)+.5)/(32*k)-.5
  y0=np.clip(np.floor(ys).astype(int),0,h-1);y1=np.clip(y0+1,0,h-1);fy=np.clip(ys-np.floor(ys),0,1)[:,None,None]
  x0=np.clip(np.floor(xs).astype(int),0,w-1);x1=np.clip(x0+1,0,w-1);fx=np.clip(xs-np.floor(xs),0,1)[None,:,None]
  d=(disp[y0][:,x0]*(1-fy)*(1-fx)+disp[y0][:,x1]*(1-fy)*fx+disp[y1][:,x0]*fy*(1-fx)+disp[y1][:,x1]*fy*fx)*k
  sx=np.clip(np.arange(W)[None,:]+d[...,0],0,W-1);sy=np.clip(np.arange(H)[:,None]+d[...,1],0,H-1)
  ix=np.floor(sx).astype(int);iy=np.floor(sy).astype(int);jx=np.minimum(ix+1,W-1);jy=np.minimum(iy+1,H-1);tx=(sx-ix)[...,None];ty=(sy-iy)[...,None]
  out=a[iy,ix]*(1-tx)*(1-ty)+a[iy,jx]*tx*(1-ty)+a[jy,ix]*(1-tx)*ty+a[jy,jx]*tx*ty
  return Image.fromarray(np.clip(out+.5,0,255).astype(np.uint8))

def summary(cells):
  good=[c for c in cells if c['score']>=MIN_SCORE]
  return {'trusted':len(good),'shifted':sum(max(abs(c['dx']),abs(c['dy']))>OUTLIER for c in good),'boundaryShifted':sum(c['flag'] and c['edge'] for c in cells)}

if __name__=='__main__':
  batch=ROOT/'production'/sys.argv[1];only=set(sys.argv[2:]);(batch/'aligned').mkdir(exist_ok=True)
  cat=json.loads((DIST/'data/catalog.json').read_text());orig={i['details']['mapId']:i for i in cat['items'] if i['category']=='maps' and not i.get('generated')}
  rules=json.loads((DIST/'data/tile-rules.json').read_text())['maps'];log_path=batch/'aligned.json';log=json.loads(log_path.read_text()) if log_path.exists() else {}
  for job in json.loads((batch/'jobs.json').read_text()):
    p=batch/f"{job['id']}.png"
    if not p.exists() or (only and job['id'] not in only):continue
    m=job['sourceId'];r=rules[m];src=Image.open(DIST/orig[m]['image']).convert('RGB');gen=Image.open(p).convert('RGB')
    before=check(src,gen,r['logic'],r['width'],r['height']);disp=np.zeros((r['height'],r['width'],2));out=gen
    for radius in ROUNDS:
      disp=disp+field(check(src,out,r['logic'],r['width'],r['height'],radius),r['width'],r['height']);out=warp(gen,disp,r['width'],r['height'])
    after=check(src,out,r['logic'],r['width'],r['height'])
    out.save(batch/'aligned'/p.name);log[job['id']]={'before':summary(before),'after':summary(after),'maxDisplacementPx':round(float(np.abs(disp).max())*gen.width/(r['width']*32),1)}
    print(job['id'],log[job['id']])
  log_path.write_text(json.dumps(log,indent=1))
