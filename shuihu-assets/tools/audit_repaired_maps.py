import json
from pathlib import Path
import numpy as np
from PIL import Image,ImageOps,ImageDraw
root=Path(__file__).resolve().parents[1]/'dist';cat=json.loads((root/'data/catalog.json').read_text());originals=[i for i in cat['items'] if i['category']=='maps' and not i.get('generated')];audit=[];representatives={}
for m in originals:
 src=np.asarray(Image.open(root/m['image']).convert('RGB'));h,w=src.shape[:2];visible=np.max(src,axis=2)>40
 for style in ['pixel-hd','unreal','ghibli']:
  id=m['details']['mapId'];row={'mapId':id,'style':style,'bankId':m['bankId']}
  for version in ['maps','maps-v2']:
   path=root/f'generated/{version}/{style}/{id}.webp'
   if not path.exists():continue
   im=Image.open(path).convert('RGB');assert im.size==(w*4,h*4)
   small=np.asarray(im.resize((w,h),Image.Resampling.BOX));row[version+'UnexpectedBlackFraction']=round(float(np.sum((np.max(small,axis=2)<12)&visible)/max(1,np.sum(visible))),6)
  row['state']='needs-visual-review';audit.append(row);representatives.setdefault((m['bankId'],style),(id,root/f'generated/maps-v2/{style}/{id}.webp'))
(root/'data/map-repair-audit.json').write_text(json.dumps({'count':len(audit),'metrics':'Unexpected near-black pixels over colored original pixels; heuristic only, not visual approval.','items':audit},indent=2))
qa=root/'repairs/qa';qa.mkdir(exist_ok=True)
values=list(representatives.items())
for n in range(0,len(values),12):
 sheet=Image.new('RGB',(1200,1280),'#efeee4');draw=ImageDraw.Draw(sheet)
 for k,((bank,style),(id,path)) in enumerate(values[n:n+12]):
  x=k%3*400;y=k//3*320;im=ImageOps.contain(Image.open(path).convert('RGB'),(390,285));sheet.paste(im,(x+(400-im.width)//2,y+28));draw.text((x+8,y+5),id+' '+style+' '+bank[5:11],fill='#172a22')
 sheet.save(qa/f'maps-{n//12+1}.jpg',quality=90)
print('Audited',len(audit),'maps; contact sheets',len(list(qa.glob('maps-*.jpg'))))
print('black ratio >4%',[(r['mapId'],r['style'],r.get('maps-v2UnexpectedBlackFraction')) for r in audit if r.get('maps-v2UnexpectedBlackFraction',0)>.04])
