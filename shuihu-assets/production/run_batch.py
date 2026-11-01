"""Durable batch worker around the unmodified imagegen CLI, no ad-hoc SDK calls."""
import concurrent.futures,json,os,subprocess,sys,time,threading
from pathlib import Path
p=Path(sys.argv[1]).resolve();jobs=json.loads((p/'jobs.json').read_text());lock=threading.Lock()
config=json.loads(Path(os.environ['SHUIHU_IMAGE_CONFIG']).read_text());env=os.environ.copy();env['OPENAI_API_KEY']=config['api_key'];cli=os.environ['SHUIHU_IMAGE_CLI']
status={j['id']:{'state':'queued'} for j in jobs}
if (p/'status.json').exists():status.update(json.loads((p/'status.json').read_text()).get('jobs',{}))
def record(j,state,**extra):
 with lock:
  status[j['id']]={'state':state,'updatedAt':time.time(),**extra};tmp=p/'status.tmp';tmp.write_text(json.dumps({'concurrency':10,'model':config['model'],'jobs':status},indent=2));tmp.replace(p/'status.json')
def run(j):
 try:
  out=p/(j['id']+'.png')
  if out.exists():record(j,'generated-awaiting-review');return
  marker=p/(j['id']+'.submitted')
  if marker.exists():record(j,'unknown-previous-attempt-no-auto-retry');return
  marker.write_text(str(time.time()));record(j,'running')
  args=[sys.executable,cli,'edit' if j.get('reference') else 'generate','--model',config['model'],'--prompt-file',str(p/(j['id']+'.txt')),'--quality','high','--size',j['size'],'--out',str(out)]
  if j.get('reference'):args+=['--image',str(p/j['reference'])]
  try:
   with (p/(j['id']+'.log')).open('w') as log:r=subprocess.run(args,env=env,stdout=log,stderr=log,timeout=1100)
   record(j,'generated-awaiting-review' if r.returncode==0 and out.exists() else 'failed',exitCode=r.returncode)
  except subprocess.TimeoutExpired:record(j,'unknown-timeout-no-auto-retry')
 except Exception as e:
  record(j,'failed',errorType=type(e).__name__)
with concurrent.futures.ThreadPoolExecutor(max_workers=10) as pool:list(pool.map(run,jobs))
