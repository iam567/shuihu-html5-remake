"""Run-to-completion collector; independent uploads fail separately and resume safely."""
import json,subprocess,time,os,sys,zipfile,hashlib,fcntl,traceback
from pathlib import Path
from publish_batch004 import publish
root=Path(__file__).resolve().parents[1];dist=root/'dist';batch=dist/'production/batch-004';statefile=root/'production/delivery-state.json';public=dist/'data/delivery-progress.json';host=os.environ.get('SHUIHU_VPS','root@130.94.65.16');repo=Path(os.environ['SHUIHU_REPO']);lock=(root/'production/delivery.lock').open('w');fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
state=json.loads(statefile.read_text()) if statefile.exists() else {'releases':{},'errors':[]};stage={}
def run(args,timeout=900):return subprocess.run(args,check=True,capture_output=True,text=True,timeout=timeout).stdout
def save():
 statefile.write_text(json.dumps(state,ensure_ascii=False,indent=2));public.write_text(json.dumps({'updatedAt':time.time(),**stage},ensure_ascii=False,indent=2))
def error(step,e):
 state['errors'].append({'time':time.time(),'step':step,'errorType':type(e).__name__});state['errors']=state['errors'][-100:];stage[step]='失败已记录，下一轮重试';save();print('ERROR',step,type(e).__name__,flush=True)
def sync_repo():
 for name in ['data','production','effects']:
  run(['rsync','-a','--exclude=*.log','--exclude=*.submitted',str(dist/name)+'/',str(repo/'shuihu-assets/dist'/name)+'/'])
 for name in ['app.js','index.html']:run(['cp',str(dist/name),str(repo/'shuihu-assets/dist'/name)])
 for name in ['production','tools']:run(['rsync','-a','--exclude=*.png','--exclude=*.zip','--exclude=*.log','--exclude=*.submitted','--exclude=*.lock','--exclude=*receipt*','--exclude=delivery-state.json','--exclude=__pycache__',str(root/name)+'/',str(repo/'shuihu-assets'/name)+'/'])
 run(['git','-C',str(repo),'add','shuihu-assets/dist/data','shuihu-assets/dist/production','shuihu-assets/dist/app.js','shuihu-assets/dist/index.html','shuihu-assets/production','shuihu-assets/tools'])
 diff=run(['git','-C',str(repo),'diff','--cached','--name-only'])
 if diff.strip():run(['git','-C',str(repo),'commit','-m','Deliver next generated art batch and update full production coverage'])
 run(['git','-C',str(repo),'push'],1800);return run(['git','-C',str(repo),'rev-parse','--short','HEAD']).strip()
while True:
 try:
  run(['rsync','-az','--exclude=*.log','--exclude=*.submitted',host+':/var/lib/shuihu-image-production/batch-004/',str(batch)+'/']);p=publish()
 except Exception as e:error('collection',e);time.sleep(30);continue
 ready=[j for j in p['jobs'] if (batch/(j['id']+'.png')).exists()];terminal=all(j['state'] not in ['queued','running'] for j in p['jobs'])
 claimed={id for r in state['releases'].values() for id in r['jobs']};fresh=[j['id'] for j in ready if j['id'] not in claimed]
 if len(fresh)>=10 or (terminal and fresh):
  ids=sorted(fresh);tag='release-'+hashlib.sha256('\n'.join(ids).encode()).hexdigest()[:12];archive=root/'production'/(tag+'.zip')
  with zipfile.ZipFile(archive,'w',zipfile.ZIP_DEFLATED) as z:
   jobs=json.loads((batch/'jobs.json').read_text());lookup={j['id']:j for j in jobs}
   for id in ids:
    for suffix in ['.png','.txt']:
     path=batch/(id+suffix)
     if path.exists():z.write(path,'assets/'+path.name)
    j=lookup[id]
    if j.get('reference'):z.write(batch/j['reference'],'references/'+j['reference'])
   z.writestr('jobs.json',json.dumps([lookup[id] for id in ids],ensure_ascii=False,indent=2));z.write(dist/'data/production-progress.json','progress.json')
  state['releases'][tag]={'jobs':ids,'archive':str(archive),'cms':False,'github':False,'workshop':False};save()
 # Workshop updates after each collection, including failures and queued status.
 try:
  run(['rsync','-az',str(batch)+'/',host+':/var/www/game-downloads/shz/production/batch-004/'])
  run(['rsync','-az',str(dist/'production/index.html'),str(dist/'production/pending.svg'),host+':/var/www/game-downloads/shz/production/'])
  run(['rsync','-az',str(dist/'data/catalog.json'),str(dist/'data/production-progress.json'),host+':/var/www/game-downloads/shz/data/'])
  run(['rsync','-az',str(dist/'app.js'),str(dist/'index.html'),host+':/var/www/game-downloads/shz/'])
  for r in state['releases'].values():r['workshop']=True
  stage['workshop']=f'已同步 {len(ready)} / {p["total"]} 张候选';save()
 except Exception as e:error('workshop',e)
 for tag,r in state['releases'].items():
  if not r['cms']:
   try:
    run([sys.executable,str(root/'production/backup_release.py'),r['archive']],1800);r['cms']=True;stage['cms']=f'已校验备份 {sum(len(v["jobs"]) for v in state["releases"].values() if v["cms"])} 张候选';save()
   except Exception as e:error('cms',e)
 if any(not r['github'] for r in state['releases'].values()):
  try:
   commit=sync_repo()
   for r in state['releases'].values():r['github']=True
   stage['github']='已上传 '+commit;save()
  except Exception as e:error('github',e)
 try:run(['rsync','-az',str(public),host+':/var/www/game-downloads/shz/data/'])
 except Exception as e:error('progress',e)
 if terminal and all(all(r[k] for k in ['workshop','cms','github']) for r in state['releases'].values()):
  state['state']='all-attempted-delivered-awaiting-review';save();print('ALL ATTEMPTED AND DELIVERED',len(ready),'generated;',p['total']-len(ready),'errors retained',flush=True);break
 print('COLLECTED',len(ready),'/',p['total'],flush=True);time.sleep(30)
