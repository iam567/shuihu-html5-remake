"""Build candidate maps from fixed atlas indices; never approves art or edits logic."""
from pathlib import Path
from PIL import Image,ImageChops
import json,hashlib,sys
from collections import deque
import numpy as np
from tile_seams import seamless,adjacency
root=Path(__file__).resolve().parents[1]/'dist';cp=root/'data/catalog.json';cat=json.loads(cp.read_text());rules=json.loads((root/'data/tile-rules.json').read_text());originals=[i for i in cat['items'] if i['category']=='maps' and not i.get('generated')];banks={i['id']:i for i in cat['items'] if i['category']=='map-banks'};styles={'pixel-hd':'高清重制','unreal':'虚幻引擎质感','ghibli':'吉卜力手绘'};cache={};tileCache={};trimAudit=[];new=[];registration=json.loads((root/'data/atlas-registration.json').read_text());patches=json.loads((root/'data/repaired-atlas-patches.json').read_text()) if (root/'data/repaired-atlas-patches.json').exists() else {};objectTiles=json.loads((root/'data/object-tile-overrides.json').read_text()) if (root/'data/object-tile-overrides.json').exists() else {};seamReport={};tileReg=json.loads((root/'data/tile-registration.json').read_text()) if (root/'data/tile-registration.json').exists() else {}
if len(sys.argv)>1:originals=[m for m in originals if m['details']['mapId'] in sys.argv[1:]]
for m in originals:
 # Keep the original exterior mask: AI atlas decoration must never spill into map void.
 sourceMap=Image.open(root/m['image']).convert('RGB');sw,sh=sourceMap.size;px=sourceMap.load();mask=Image.new('L',(sw,sh));mp=mask.load();queue=deque()
 for x in range(sw):queue.append((x,0));queue.append((x,sh-1))
 for y in range(sh):queue.append((0,y));queue.append((sw-1,y))
 while queue:
  x,y=queue.popleft()
  if x<0 or y<0 or x>=sw or y>=sh or mp[x,y] or max(px[x,y])>2:continue
  mp[x,y]=255;queue.extend(((x-1,y),(x+1,y),(x,y-1),(x,y+1)))
 mask=mask.resize((sw*4,sh*4),Image.Resampling.NEAREST)
 data=rules['maps'][m['details']['mapId']];bank=banks[data['bankId']]
 for style,label in styles.items():
  key=(bank['id'],style)
  if key not in cache:
   files=list((root/'production').glob('batch-*/'+bank['id']+'-'+style+'.png'))
   if len(files)!=1:raise ValueError((key,files))
   # Scale whole atlas to fixed slots; geometry remains unverified until visual review.
   patch=patches.get(bank['id']+'-'+style);cache[key]=(Image.open(root/patch['image'] if patch else files[0]).convert('RGB'),Image.open(root/bank['image']).convert('RGB'))
  atlas,source=cache[key];alignment=registration[bank['id']+'-'+style]
  regTiles=None if bank['id']+'-'+style in patches else tileReg.get(bank['id']+'-'+style,{}).get('tiles')
  if regTiles and (bank['id'],style,'seamless') not in tileCache:
   # Cut every registered tile once, then make repeated ground tiles join like the originals (tile_seams.py).
   cols=bank['width']//32;arrays={};originals={};groundMasks={}
   for t,reg in regTiles.items():
    t=int(t);originals[t]=np.asarray(source.crop((t%cols*32,t//cols*32,t%cols*32+32,t//cols*32+32)))
    override=objectTiles.get(bank['id']+'-'+style,{}).get(str(t))
    # Tiles redrawn as part of a whole object (extract_object_sheets.py) replace the atlas cut.
    # Boxes at the atlas border can reach past the image; move them inside rather than letting transform fill black.
    q=list(reg['quad']);xs,ys=q[0::2],q[1::2];sx=max(0,-min(xs))-max(0,max(xs)-atlas.width);sy=max(0,-min(ys))-max(0,max(ys)-atlas.height)
    q=[v+(sx if i%2==0 else sy) for i,v in enumerate(q)]
    if override and override.get('groundMask'):groundMasks[t]=np.asarray(Image.open(root/override['groundMask']))>127
    arrays[t]=np.asarray(Image.open(root/override['image']).convert('RGB')) if override else np.asarray(atlas.transform((128,128),Image.Transform.QUAD,q,Image.Resampling.BICUBIC))
   fixed,report=seamless(arrays,originals,adjacency(rules,bank['id']),groundMasks);seamReport[bank['id']+'-'+style]=report
   for t,a in fixed.items():tileCache[(bank['id'],style,t)]=Image.fromarray(a)
   tileCache[(bank['id'],style,'seamless')]=True
  if bank['id']+'-'+style in patches:alignment={'columnBounds':list(range(0,atlas.width+1,128)),'rowBounds':list(range(0,atlas.height+1,128))}
  im=Image.new('RGB',(data['width']*128,data['height']*128));cols=bank['width']//32
  for n,t in enumerate(data['graphics']):
   col,row=t%cols,t//cols
   x1,x2=alignment['columnBounds'][col:col+2];y1,y2=alignment['rowBounds'][row:row+2]
   original=source.crop((col*32,row*32,col*32+32,row*32+32))
   tileKey=(bank['id'],style,t)
   registered=None if bank['id']+'-'+style in patches else tileReg.get(bank['id']+'-'+style,{}).get('tiles',{}).get(str(t))
   if tileKey not in tileCache and registered:
    # Per-tile registration (register_tiles.py): crop the located cell, kept inside the atlas, with no trimming.
    tileCache[tileKey]=Image.new('RGB',(128,128)) if max(original.getextrema()[k][1] for k in range(3))<12 else atlas.transform((128,128),Image.Transform.QUAD,registered['quad'],Image.Resampling.BICUBIC)
   if tileKey not in tileCache:
    cut=atlas.crop((x1,y1,x2,y2));cw,ch=cut.size;left,top,right,bottom=0,0,cw,ch
    # Fully painted source tiles cannot legitimately acquire a black gutter.
    sourceBlack=sum(max(v)<12 for v in original.getdata())/1024
    if sourceBlack<.01:
     pix=cut.load()
     def darkCol(x):return sum(max(pix[x,y])<24 for y in range(top,bottom))/max(1,bottom-top)
     def darkRow(y):return sum(max(pix[x,y])<24 for x in range(left,right))/max(1,right-left)
     while left<int(cw*.19) and darkCol(left)>.15:left+=1
     while right>cw-int(cw*.19) and darkCol(right-1)>.15:right-=1
     while top<int(ch*.19) and darkRow(top)>.15:top+=1
     while bottom>ch-int(ch*.19) and darkRow(bottom-1)>.15:bottom-=1
    if (left,top,right,bottom)!=(0,0,cw,ch):trimAudit.append({'bank':bank['id'],'style':style,'tile':t,'originalBox':[x1,y1,x2,y2],'contentBox':[x1+left,y1+top,x1+right,y1+bottom],'reason':'generated black padding on originally fully painted tile'})
    tile=Image.new('RGB',(128,128)) if max(original.getextrema()[k][1] for k in range(3))<12 else cut.crop((left,top,right,bottom)).resize((128,128),Image.Resampling.LANCZOS)
    tileCache[tileKey]=tile
   im.paste(tileCache[tileKey],(n%data['width']*128,n//data['width']*128))
  im.paste((0,0,0),(0,0),mask)
  id=m['details']['mapId'];file=f'generated/maps-v2/{style}/{id}.webp';out=root/file;out.parent.mkdir(parents=True,exist_ok=True);im.save(out,'WEBP',quality=94,method=3)
  new.append({**m,'id':f'map-{id}-{style}','name':f'地图{id[:2]}-{id[2:]} · {label}','image':file,'width':im.width,'height':im.height,'generated':True,'style':style,'sha256':hashlib.sha256(out.read_bytes()).hexdigest(),'status':'registered-repair-awaiting-review','productionState':'repair-candidate','confidence':{'level':'candidate','basis':'Original map graphic indices used unchanged','limit':'逐块配准图集位置（register_tiles.py），避免整图网格漂移造成的错切与邻块黑边，并恢复原版空白格；这是修复候选，仍需检查接缝、遮挡与招牌。'}})
cat=json.loads(cp.read_text());cat['items']=[i for i in cat['items'] if i['id'] not in {v['id'] for v in new}]+new
for c in cat['categories']:
 c['count']=sum(i['category']==c['id'] for i in cat['items'])
cp.write_text(json.dumps(cat,ensure_ascii=False));(root/'data/atlas-trim-audit.json').write_text(json.dumps(trimAudit,indent=2));(root/'data/tile-seam-report.json').write_text(json.dumps(seamReport));(root/'data/generated-maps.json').write_text(json.dumps({'status':'awaiting-visual-review','count':sum(i['category']=='maps' and bool(i.get('generated')) for i in cat['items']),'items':[i for i in cat['items'] if i['category']=='maps' and i.get('generated')]},ensure_ascii=False));print('Assembled candidate maps:',len(new))
