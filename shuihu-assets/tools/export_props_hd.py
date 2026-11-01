"""Fit the prop redraws (production/props-hd-1, prepare_props_hd.py) to the original props' footprints.

Every prop is drawn at 4x its original size, as the hd2d maps are, on a canvas with room for its shadow (PX, PY;
props.json hd.dx/dy/w/h give the drawn box in original pixels). A redraw on magenta is keyed (slice_ui_buttons.key),
trimmed to its opaque bounds, laid on a soft ground shadow (shadow()) and scaled to the original's opaque height x4 (no more than 1.25x its width, since a
redraw's proportions differ a little and matching the narrower side made figures visibly smaller), centred horizontally and standing on the original's bottom edge. The cave is cut out of
its redrawn map crop along the original cave's outline. A prop with no redraw (the image service refused 林娘子 shot by an
arrow, so it is not resubmitted) is enlarged from its own pixels with Scale2x twice: no new content at all.
Writes shuihu-html5/dist/assets/props-hd/prop-NN.webp (one per bit, duplicates share the picture) and adds "hd" entries
to dist/data/props.json, each with status "review" until the user approves it.
Usage: python3 tools/export_props_hd.py
"""
import json
from pathlib import Path
import numpy as np
from PIL import Image,ImageFilter
from slice_ui_buttons import key

ROOT=Path(__file__).resolve().parents[1];GAME=ROOT.parent/'shuihu-html5/dist';BATCH=ROOT/'production/props-hd-1';OUT=GAME/'assets/props-hd'
SAME={3:2,10:5,13:12,14:12}

def scale2x(a):
  p=np.pad(a,((1,1),(1,1),(0,0)),mode='edge');B,D,E,F,H=p[:-2,1:-1],p[1:-1,:-2],p[1:-1,1:-1],p[1:-1,2:],p[2:,1:-1]
  eq=lambda x,y:(x==y).all(-1)[...,None];ok=~eq(B,H)&~eq(D,F)
  e0=np.where(ok&eq(D,B),D,E);e1=np.where(ok&eq(B,F),F,E);e2=np.where(ok&eq(D,H),D,E);e3=np.where(ok&eq(H,F),F,E)
  out=np.empty((a.shape[0]*2,a.shape[1]*2,4),a.dtype);out[0::2,0::2]=e0;out[0::2,1::2]=e1;out[1::2,0::2]=e2;out[1::2,1::2]=e3;return out

def bounds(a):
  ys,xs=np.nonzero(a[...,3]>40);return xs.min(),ys.min(),xs.max()+1,ys.max()+1

def dither(o):
  """The original's ground shadow: lone black pixels in a checkerboard (no opaque neighbour up, down, left or right)."""
  A=o[...,3]>0;p=np.pad(A,1);return A&(o[...,:3].sum(-1)<60)&~p[:-2,1:-1]&~p[2:,1:-1]&~p[1:-1,:-2]&~p[1:-1,2:]

PX,PY=8,6   # room (original pixels) left and right of and below each prop for its shadow to fall into

def shadow(orig,solid):
  """A dark ground shadow at 4x on a canvas PX wider on each side and PY taller: an ellipse under the base with the
  people's falloff in app.js sprite() (.8 / .62 / 0), joined by the original's own checkerboard shadow where it has one
  (filled in, blurred, .85)."""
  o=np.asarray(orig);d=dither(o);W,H=(orig.width+2*PX)*4,(orig.height+PY)*4
  x0,y0,x1,y1=bounds(solid);cx,cy=(x0+x1)/2*4+PX*4,y1*4-6;rx,ry=max(56,(x1-x0)*4*0.5),22
  yy,xx=np.mgrid[0:H,0:W];r=np.sqrt(((xx-cx)/rx)**2+((yy-cy)/ry)**2);alpha=np.interp(r,[0,.55,1],[.8,.62,0],right=0)
  if d.sum()>=4:
    p=np.pad(d,1);m=d|p[:-2,1:-1]|p[2:,1:-1]|p[1:-1,:-2]|p[1:-1,2:]|p[:-2,:-2]|p[:-2,2:]|p[2:,:-2]|p[2:,2:]
    m=np.pad(m,((0,PY),(PX,PX)));a=Image.fromarray((m*255).astype(np.uint8)).resize((W,H),Image.Resampling.NEAREST).filter(ImageFilter.GaussianBlur(4))
    alpha=np.maximum(alpha,np.asarray(a).astype(float)/255*0.85)
  out=np.zeros((H,W,4),np.uint8);out[...,3]=np.round(alpha*255).astype(np.uint8);return Image.fromarray(out)

def fit(hd,orig):
  solid=np.asarray(orig).copy();solid[dither(solid)]=0
  ox0,oy0,ox1,oy1=[v*4 for v in bounds(solid)]   # the figure itself, without its checkerboard shadow
  a=np.asarray(hd).astype(np.uint8).copy();a[a[...,3]<64]=0   # faint magenta haze the key leaves along the canvas edges
  x0,y0,x1,y1=bounds(a);fig=Image.fromarray(a[y0:y1,x0:x1])
  k=min((oy1-oy0)/fig.height,1.25*(ox1-ox0)/fig.width);fig=fig.resize((max(1,round(fig.width*k)),max(1,round(fig.height*k))),Image.Resampling.LANCZOS)
  out=shadow(orig,solid);out.alpha_composite(fig,(round((ox0+ox1-fig.width)/2)+PX*4,oy1-fig.height));return out

if __name__=='__main__':
  OUT.mkdir(parents=True,exist_ok=True);data=json.loads((GAME/'data/props.json').read_text());meta=json.loads((BATCH/'meta.json').read_text())
  pics={}
  for p in data['props']:
    bit=SAME.get(p['bit'],p['bit']);src=BATCH/f'prop-{bit:02d}.png';orig=Image.open(GAME/p['image']).convert('RGBA')
    if bit not in pics:
      if bit==11 and src.exists():
        x0,y0,w,h=meta['prop-11']['crop'];crop=Image.open(src).convert('RGBA').resize((w,h),Image.Resampling.LANCZOS)
        mask=orig.resize((orig.width*4,orig.height*4),Image.Resampling.NEAREST).getchannel('A')
        pic=crop.crop((p['x']*4-x0,p['y']*4-y0,p['x']*4-x0+mask.width,p['y']*4-y0+mask.height));pic.putalpha(mask);how='redraw';pad=(0,0)
      elif src.exists():pic=fit(key(Image.open(src)),orig);how='redraw';pad=(PX,PY)
      else:
        solid=np.asarray(orig).copy();solid[dither(solid)]=0;pic=shadow(orig,solid);pic.alpha_composite(Image.fromarray(scale2x(scale2x(solid))),(PX*4,0));how='scale2x';pad=(PX,PY)
      name=f'assets/props-hd/prop-{bit:02d}.webp';pic.save(GAME/name,lossless=True);pics[bit]=(name,how,pad)
    name,how,(px,py)=pics[bit];p['hd']={'image':name,'source':how,'dx':p['dx']-px,'dy':p['dy'],'w':p['w']+2*px,'h':p['h']+py,'status':p.get('hd',{}).get('status','review')}
  (GAME/'data/props.json').write_text(json.dumps(data,ensure_ascii=False,indent=1))
  print({b:h for b,(n,h,_) in pics.items()})
