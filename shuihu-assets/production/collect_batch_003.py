"""Collect the running VPS batch and back it up once; never calls image API."""
import json,subprocess,time,sys,os
from pathlib import Path
root=Path(__file__).resolve().parents[1];status=root/'production/collection-003.json';host=os.environ.get('SHUIHU_VPS','root@130.94.65.16')
def run(args):return subprocess.run(args,check=True,capture_output=True,text=True).stdout
def note(state,**extra):status.write_text(json.dumps({'state':state,**extra},indent=2))
try:
 while True:
  data=json.loads(run(['ssh',host,'cat /var/lib/shuihu-image-production/batch-003/status.json']))
  jobs=data['jobs'];note('waiting-for-generation',jobs=len(jobs),finished=sum(j['state']!='running' for j in jobs.values()))
  if len(jobs)==87 and all(j['state']!='running' for j in jobs.values()):break
  time.sleep(30)
 dest=root/'dist/production/batch-003';dest.mkdir(parents=True,exist_ok=True)
 run(['rsync','-a','--exclude=*.submitted','--exclude=*.log',host+':/var/lib/shuihu-image-production/batch-003/',str(dest)+'/'])
 note('backing-up-cms')
 run([sys.executable,str(root/'upload_batch_003.py')])
 note('publishing-vps')
 run(['rsync','-a',str(dest)+'/',host+':/var/www/game-downloads/shz/production/batch-003/'])
 note('backed-up-awaiting-review',generated=sum(j['state']=='generated-awaiting-review' for j in jobs.values()),failed=sum(j['state']!='generated-awaiting-review' for j in jobs.values()))
except Exception as e:
 note('collection-failed',errorType=type(e).__name__)
 raise
