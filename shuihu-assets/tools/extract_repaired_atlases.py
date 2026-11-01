"""Extract isolated cell artworks using magenta gutters, retaining source tile indices."""
from pathlib import Path
from PIL import Image
import json
root=Path(__file__).resolve().parents[1]/'dist';batch=root/'production/batch-005';out=root/'generated/repaired-atlases';out.mkdir(parents=True,exist_ok=True);jobs=json.loads((batch/'jobs.json').read_text());patches={};qa=[]
for j in jobs:
 p=batch/(j['id']+'.png')
 if not p.exists():continue
 source=Image.open(root/'assets'/(j['sourceId']+'.png')).convert('RGB');im=Image.open(p).convert('RGB');cols,rows=j['columns'],j['rows'];count=cols*rows;packed=Image.new('RGB',(16*128,((count+15)//16)*128))
 for n in range(count):
  orig=source.crop((n%16*32,n//16*32,n%16*32+32,n//16*32+32))
  if max(max(v) for v in orig.getdata())<12:continue
  x0=round(n%cols*im.width/cols);y0=round(n//cols*im.height/rows);x1=round((n%cols+1)*im.width/cols);y1=round((n//cols+1)*im.height/rows);cell=im.crop((x0,y0,x1,y1));px=cell.load();valid=[]
  for y in range(cell.height):
   for x in range(cell.width):
    r,g,b=px[x,y]
    if not(r>g+35 and b>g+35 and r>110 and b>100):valid.append((x,y))
  if not valid:raise ValueError('Empty cell '+j['id']+' '+str(n))
  left=max(round(cell.width*.095),min(p[0] for p in valid));right=min(round(cell.width*.905),max(p[0] for p in valid)+1);top=max(round(cell.height*.095),min(p[1] for p in valid));bottom=min(round(cell.height*.905),max(p[1] for p in valid)+1)
  assert right-left>cell.width*.55 and bottom-top>cell.height*.55,(j['id'],n,'missing core')
  tile=cell.crop((left+1,top+1,right-1,bottom-1)).resize((128,128),Image.Resampling.LANCZOS);packed.paste(tile,(n%16*128,n//16*128));qa.append({'job':j['id'],'tile':n,'contentBox':[x0+left+1,y0+top+1,x0+right-1,y0+bottom-1]})
 path=out/(j['sourceId']+'-'+j['style']+'.png');packed.save(path);patches[j['sourceId']+'-'+j['style']]={'image':str(path.relative_to(root)),'columns':16,'tileSize':128,'status':'repainted-awaiting-review'}
(root/'data/repaired-atlas-patches.json').write_text(json.dumps(patches,indent=2));(root/'data/repaired-atlas-extraction.json').write_text(json.dumps(qa,indent=2));print('Repacked',len(patches),'atlases;',len(qa),'cells')
