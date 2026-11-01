"""Fit atlas coordinate registration from source blank-space masks; no art repainting."""
import json
from pathlib import Path
import numpy as np
from PIL import Image
ROOT=Path(__file__).resolve().parents[1]/'dist'
def register(srcpath,dstpath):
 src=Image.open(srcpath).convert('RGB');dst=Image.open(dstpath).convert('RGB');a=np.array(src);b=np.array(dst);h,w=a.shape[:2];H,W=b.shape[:2]
 # Original pure-black pixels mark unused atlas slots; generated padding must be outside this shape.
 yy,xx=np.mgrid[2:h:4,2:w:4];orig=np.max(a[yy,xx],axis=2)>12;target=np.max(b,axis=2)>18
 def cost(p):
  x0,y0,sx,sy=p;x=np.rint(x0+xx*sx).astype(int);y=np.rint(y0+yy*sy).astype(int);valid=(x>=0)&(x<W)&(y>=0)&(y<H);actual=target[np.clip(y,0,H-1),np.clip(x,0,W-1)]&valid
  # Balance foreground/background so sparse atlases cannot score by selecting a blank region.
  err=((~actual)&orig).sum()/max(1,orig.sum())+((actual)&~orig).sum()/max(1,(~orig).sum())
  return float(err)+.002*abs(sx-sy)/max(sx,sy)
 scale=W/w;starts=[]
 for sy in [scale, min(scale,H/h),H/h]:
  for y0 in np.linspace(0,max(0,H-h*sy),11):starts.append([0,float(y0),scale,sy])
 p=min(starts,key=cost);best=cost(p)
 for delta in [16,8,4,2,1,.5]:
  for _ in range(12):
   change=False
   for k,d in enumerate([delta,delta,delta/w,delta/h]):
    for sign in [-1,1]:
     q=p.copy();q[k]+=sign*d
     if q[2]<=0 or q[3]<=0:continue
     score=cost(q)
     if score+1e-9<best:p,best=q,score;change=True
   if not change:break
 # Generation pads over-wide atlases into the provider's maximum aspect ratio.
 # Keep the full width exact: shifting it by a handful of pixels contaminates every cell.
 scale=W/w
 if abs((W/H)/(w/h)-1)<.04:
  xs=[round(col*W/(w//32)) for col in range(w//32+1)]
  ys=[round(row*H/(h//32)) for row in range(h//32+1)]
  return {'columnBounds':xs,'rowBounds':ys,'x':0,'y':0,'scaleX':W/w,'scaleY':H/h,'maskError':best,'sourceSize':[w,h],'generatedSize':[W,H],'method':'aspect-matched-exact-grid','status':'alignment-candidate-needs-visual-review'}
 p=[0,max(0,(H-h*scale)/2),scale,scale]
 # Snap horizontal boundaries near the centered source region, keeping exact columns.
 grad=np.mean(np.abs(np.diff(b.astype(float),axis=0)),axis=(1,2))
 ys=[]
 for row in range(h//32+1):
  center=p[1]+row*32*p[3];radius=max(8,32*p[3]*.17)
  lo=max(1,int(center-radius));hi=min(H-1,int(center+radius))
  boundary=int(np.argmax(grad[lo-1:hi])+lo) if hi>lo else max(0,min(H,round(center)))
  ys.append(boundary)
 xs=[max(0,min(W,round(col*W/(w//32)))) for col in range(w//32+1)]
 return {'columnBounds':xs,'rowBounds':ys,'x':p[0],'y':p[1],'scaleX':p[2],'scaleY':p[3],'maskError':best,'sourceSize':[w,h],'generatedSize':[W,H],'method':'source-black-slot-mask-registration','status':'alignment-candidate-needs-visual-review'}
if __name__=='__main__':
 import sys
 c=json.loads((ROOT/'data/catalog.json').read_text());banks=[i for i in c['items'] if i['category']=='map-banks'];data={}
 if len(sys.argv)>1:banks=[i for i in banks if i['id'] in sys.argv[1:]]
 for bank in banks:
  for style in ['pixel-hd','unreal','ghibli']:
   paths=list((ROOT/'production').glob('batch-*/'+bank['id']+'-'+style+'.png'))
   if not paths:continue
   p=register(ROOT/bank['image'],paths[0]);p['image']=str(paths[0].relative_to(ROOT));data[bank['id']+'-'+style]=p;print(bank['id'],style,round(p['y'],2),round(p['scaleY'],3),round(p['maskError'],4),flush=True)
 out=ROOT/'data/atlas-registration.json'
 if out.exists():data={**json.loads(out.read_text()),**data}
 out.write_text(json.dumps(data,ensure_ascii=False,indent=2))
