"""Build code-native pixel sprite sheets, 4x4 cells, 16 authored time steps."""
import math,json
from pathlib import Path
OUT=Path(__file__).resolve().parents[1]/'dist/effects/sheets'
S=96
items=[(3,'slash',['#17375e','#247eb7','#51cfed','#c4ffff','#ffffff']),(22,'arrow',['#254e43','#438959','#85c967','#dbefa2','#ffffff']),(33,'thrust',['#34224f','#6b4097','#af79df','#edd1ff','#ffffff']),(46,'shot',['#65303a','#b74932','#ef8c35','#ffda83','#fffce2']),(65,'fire',['#6b2741','#bb3f35','#ef7733','#ffc65a','#fff0bd'])]
for id,kind,pal in items:
 frames=[]
 for f in range(16):
  pix={};t=f/15
  def dot(x,y,c,r=0):
   x,y=round(x),round(y)
   for dy in range(-r,r+1):
    for dx in range(-r,r+1):
     if 0<=x+dx<S and 0<=y+dy<S:pix[x+dx,y+dy]=c
  def line(x,y,xx,yy,c,r=0):
   n=max(1,int(max(abs(xx-x),abs(yy-y))))
   for i in range(n+1):dot(x+(xx-x)*i/n,y+(yy-y)*i/n,c,r)
  if kind=='slash':
   if f<12:
    tip=-2.6+f*.34
    for j in range(90):
     a=tip-j*.014
     # Three crisp concentric bands of a sweeping crescent.
     for rr,c in [(29,1),(27,2),(25,3),(24,4)]:
      if j<80-rr:dot(49+math.cos(a)*rr,47+math.sin(a)*rr,c,1)
  elif kind in ('arrow','thrust','shot'):
   x=12+min(f/8,1)*56;y=46
   if f<=8:
    length={'arrow':20,'thrust':38,'shot':14}[kind]
    line(x-length,y,x,y,2,1);line(x-length+4,y,x,y,3)
    line(x,y,x-5,y-4,3);line(x,y,x-5,y+4,3)
    if kind=='arrow':
     line(x-length,y,x-length-5,y-4,1);line(x-length,y,x-length-5,y+4,1)
    if kind=='shot' and f<4:
     for k in range(8):
      a=k*math.pi/4;line(13,46,13+math.cos(a)*(10-f*2),46+math.sin(a)*(10-f*2),3)
  else:
   for k in range(7):
    p=(f-k*.6)/14
    if 0<p<1:
     x=48+math.sin(k*3.1)*16;y=66-p*40;w=5+math.sin(p*math.pi)*5;h=9+math.sin(p*math.pi)*14
     for yy in range(int(y-h),int(y+h/2)):
      width=max(0,w*(1-abs((yy-y)/h)))
      for xx in range(int(x-width),int(x+width)):
       dot(xx,yy, min(4,1+int((1-abs(xx-x)/max(1,width))*3)))
  if f>=8:
   p=(f-8)/7;cx=48 if kind in ('slash','fire') else 68;cy=47
   for k in range(10):
    a=k*2.399;rad=5+p*24
    x=cx+math.cos(a)*rad;y=cy+math.sin(a)*rad+p*p*6
    if f<15 and k%3<=15-f:dot(x,y,3 if k%2 else 2,1 if f<12 else 0)
   if f in (8,9):
    for k in range(8):
     a=k*math.pi/4;line(cx,cy,cx+math.cos(a)*12,cy+math.sin(a)*12,4)
  ox=f%4*S;oy=f//4*S
  frames.extend(f'<rect x="{x+ox}" y="{y+oy}" width="1" height="1" fill="{pal[c]}"/>' for (x,y),c in pix.items())
 (OUT/f'item-{id}.svg').write_text('<svg xmlns="http://www.w3.org/2000/svg" width="384" height="384" viewBox="0 0 384 384" shape-rendering="crispEdges">'+''.join(frames)+'</svg>')
(OUT/'manifest.json').write_text(json.dumps({'version':1,'frameWidth':96,'frameHeight':96,'columns':4,'rows':4,'frameCount':16,'fps':16,'background':'transparent','status':'prototype-awaiting-review','items':[{'id':id,'sheet':f'item-{id}.svg','kind':kind,'impactFrame':8} for id,kind,_ in items]},indent=2))
print('Built 5 pixel sprite sheets: 16 frames each, 96x96 transparent cells')
