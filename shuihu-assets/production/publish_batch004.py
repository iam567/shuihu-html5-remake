"""Index generated candidates and expose the full remaining queue; no API calls."""
import json,copy,time
from pathlib import Path
from PIL import Image
root=Path(__file__).resolve().parents[1];dist=root/'dist';batch=dist/'production/batch-004'
def write(p,d):
 tmp=p.with_suffix(p.suffix+'.tmp');tmp.write_text(json.dumps(d,ensure_ascii=False,indent=2));tmp.replace(p)
def publish():
 jobs=json.loads((batch/'jobs.json').read_text());status=json.loads((batch/'status.json').read_text()) if (batch/'status.json').exists() else {'jobs':{}}
 cat=json.loads((dist/'data/catalog.json').read_text());cat['items']=[i for i in cat['items'] if i.get('productionBatch')!='batch-004'];lookup={i['id']:i for i in cat['items']};counts={}
 placeholder=dist/'production/pending.svg';placeholder.write_text('<svg xmlns="http://www.w3.org/2000/svg" width="256" height="256"><rect width="256" height="256" fill="#e5e7dd"/><text x="128" y="130" text-anchor="middle" font-size="20" fill="#5b6d5c" font-family="sans-serif">待生成</text></svg>')
 for j in jobs:
  path=batch/(j['id']+'.png');state=status['jobs'].get(j['id'],{}).get('state','queued');ok=path.exists();kind=j['kind'];counts.setdefault(kind,dict(total=0,generated=0,failed=0,running=0));counts[kind]['total']+=1
  counts[kind]['generated']+=ok;counts[kind]['failed']+=state.startswith(('failed','unknown','blocked'));counts[kind]['running']+=state=='running'
  if ok:
   with Image.open(path) as im:w,h=im.size
  else:w=h=256
  def entry(id,name,category,image,details):
   return dict(id=id,name=name,category=category,image=image,width=w,height=h,details=details,productionBatch='batch-004',generated=ok,productionState='generated-awaiting-review' if ok else state,confidence={'limit':'已生成候选，尚待逐张检查：人物朝向与步态、头像身份、图标对应关系和透明背景；不可视为实战验收。' if ok else '待生成任务；此卡片用于列全制作范围，不代表已完成。'})
  image=str(path.relative_to(dist)) if ok else 'production/pending.svg'
  if kind=='item-icons':
   for n,item in enumerate(j['items']):
    icon=path.parent/'icons'/f'item-{item["id"]}.png'
    if ok and not icon.exists():
     icon.parent.mkdir(exist_ok=True)
     with Image.open(path) as im:
      cw,ch=im.width//4,im.height//4;im.crop((n%4*cw,n//4*ch,(n%4+1)*cw,(n//4+1)*ch)).save(icon)
    e=entry('item-style-'+str(item['id']),item['name']+' · 物品样式','items',str(icon.relative_to(dist)) if ok else image,{'itemId':item['id'],'atlasId':j['id']});e['width']=w//4 if ok else 256;e['height']=h//4 if ok else 256;cat['items'].append(e)
  else:
   category={'character':'characters','portrait':'portraits','interface':'ui-hd'}[kind]
   label={'character':'人物精灵 · 九帧重绘','portrait':'人物头像 · 高清重绘','interface':'高清界面'}[kind]
   details=copy.deepcopy(lookup.get(j.get('sourceId'),{}).get('details',{}));details.update(sourceId=j.get('sourceId'),frameCount=9 if kind=='character' else 1)
   if kind=='character':details.update(layout='3x3',frameWidth=w/3,frameHeight=h/3,sequence=['front-idle','front-left','front-right','back-idle','back-left','back-right','side-idle','side-left','side-right'],mirrorSide=True,specialFrames='separate-runtime-effect-not-approved')
   labels={'ui-dialogue-hd':'对话框','ui-shop-hd':'商店购买面板','ui-inventory-hd':'物品背包','ui-character-status-hd':'人物状态','ui-settings-hd':'设置面板','ui-battle-hd':'战斗面板','ui-buttons-hd':'触摸按钮','ui-save-load-hd':'存读档面板'}
   e=entry(j['id'],labels.get(j['id'],j.get('sourceId',''))+' · '+label,category,image,details)
   if kind=='character' and ok:e['previewUrl']='animation/'
   cat['items'].append(e)
 for i in cat['items']:
  if i['id']=='character-100400-hd' or ('character-100400-hd' in i.get('image','') and i['category']=='hd-candidates'):
   i['productionState']='rejected';i['name']='旧版人物精灵 · 已退回重绘';i['confidence']['limit']='用户指出朝向、步行帧顺序错误，禁止用于游戏；由九帧重绘版本替代。'
 categories={x['id']:x for x in cat['categories']};categories.setdefault('ui-hd',{'id':'ui-hd','name':'高清界面','count':0})
 for k,v in categories.items():v['count']=sum(i['category']==k for i in cat['items'])
 cat['categories']=list(categories.values());cat['totalItems']=len(cat['items']);write(dist/'data/catalog.json',cat)
 progress={'updatedAt':time.time(),'batch':'batch-004','total':len(jobs),'counts':counts,'jobs':[dict(id=j['id'],kind=j['kind'],state=status['jobs'].get(j['id'],{}).get('state','queued')) for j in jobs],'items':json.loads((batch/'item-register.json').read_text()),'note':'生成成功不等于验收通过，旧错误人物图已退回；失败任务保留，其他任务继续。'};write(dist/'data/production-progress.json',progress)
 return progress
if __name__=='__main__':print(json.dumps(publish()['counts']))
