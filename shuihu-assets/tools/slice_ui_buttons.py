"""Cut generated button sheets (magenta background, text painted in) into single transparent button images.

Magenta is keyed out with soft alpha (excess of min(r,b) over g), so glows stay translucent; their remaining tint is
pulled towards gold for names ending in -on (the selected state). Buttons are found as connected opaque regions,
ordered top-to-bottom then left-to-right, and must match the given names one to one. Each is saved at HEIGHT px tall.
Usage: python3 tools/slice_ui_buttons.py SHEET.png OUTDIR name1 name2 ...
"""
import sys
from collections import deque
from pathlib import Path
import numpy as np
from PIL import Image

HEIGHT,ROW=104,120

def key(im):
  a=np.asarray(im.convert('RGB')).astype(np.float32);r,g,b=a[...,0],a[...,1],a[...,2]
  ex=np.clip(np.minimum(r,b)-g,0,255);alpha=np.where(ex>=230,0,np.where(ex<=20,1,1-ex/255));safe=np.maximum(alpha,1e-3);k=ex*(ex>20)
  out=np.dstack([np.clip((r-k)/safe,0,255),np.clip(g/safe,0,255),np.clip((b-k)/safe,0,255),alpha*255]);out[alpha<=0]=0
  return out

def boxes(alpha,step=4,min_cells=300):
  small=alpha[::step,::step]>235;H,W=small.shape;seen=np.zeros((H,W),bool);found=[]
  for y in range(H):
    for x in range(W):
      if not small[y,x] or seen[y,x]:continue
      q=deque([(y,x)]);seen[y,x]=True;y0=y1=y;x0=x1=x;n=0
      while q:
        cy,cx=q.popleft();n+=1;y0,y1,x0,x1=min(y0,cy),max(y1,cy),min(x0,cx),max(x1,cx)
        for ny,nx in((cy+1,cx),(cy-1,cx),(cy,cx+1),(cy,cx-1)):
          if 0<=ny<H and 0<=nx<W and small[ny,nx] and not seen[ny,nx]:seen[ny,nx]=True;q.append((ny,nx))
      if n>min_cells:found.append((x0*step,y0*step,(x1+1)*step,(y1+1)*step))
  return sorted(found,key=lambda b:(round((b[1]+b[3])/2/ROW),b[0]))

if __name__=='__main__':
  sheet,out,names=Path(sys.argv[1]),Path(sys.argv[2]),sys.argv[3:];out.mkdir(parents=True,exist_ok=True)
  rgba=key(Image.open(sheet));found=boxes(rgba[...,3])
  assert len(found)==len(names),f'{len(found)} buttons found, {len(names)} names given: {found}'
  for name,(x0,y0,x1,y1) in zip(names,found):
    pad=14 if name.endswith('-on') else 6;a=rgba[max(0,y0-pad):y1+pad,max(0,x0-pad):x1+pad].copy()
    if name.endswith('-on'):
      glow=(a[...,3]<0.92*255)&(a[...,3]>0);a[glow,:3]=a[glow,:3]*0.3+np.array([255,206,110])*0.7
    c=Image.fromarray(a.astype(np.uint8));c=c.resize((round(c.width*HEIGHT/c.height),HEIGHT),Image.Resampling.LANCZOS)
    c.save(out/f'{name}.webp','WEBP',quality=92,method=6);print(name,c.size)
