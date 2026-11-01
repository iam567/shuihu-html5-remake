"""Publish regenerated style maps to the asset workshop (game.areu.pro/shz) without overwriting newer server edits.

For each map id: back up the server's current files, upload generated/maps-v2/<style>/<id>.webp, re-embed the new base
image in generated/maps-signage/<style>/<id>.svg when that sign-layer map exists, and update only those items in the
server's own data/catalog.json and data/generated-maps.json (sha256, size, status). Extra data files given with
--data are copied as-is. Usage:
  python3 tools/publish_workshop_maps.py MAPID ... [--data data/tile-seam-report.json ...]
Environment: SHUIHU_WORKSHOP (default root@130.94.65.16:/var/www/game-downloads/shz).
"""
import base64,hashlib,json,os,re,subprocess,sys,tempfile,time
from pathlib import Path

DIST=Path(__file__).resolve().parents[1]/'dist';STYLES=['pixel-hd','unreal','ghibli']
TARGET=os.environ.get('SHUIHU_WORKSHOP','root@130.94.65.16:/var/www/game-downloads/shz');HOST,ROOT=TARGET.split(':',1)
args=sys.argv[1:];data=args[args.index('--data')+1:] if '--data' in args else [];maps=args[:args.index('--data')] if '--data' in args else args
ssh=lambda cmd:subprocess.run(['ssh','-o','BatchMode=yes',HOST,cmd],check=True,capture_output=True,text=True).stdout
def pull(rel,dst):subprocess.run(['scp','-q','-o','BatchMode=yes',f'{HOST}:{ROOT}/{rel}',str(dst)],check=True)
def push(src,rel):subprocess.run(['rsync','-a','--no-owner','--no-group','-e','ssh -o BatchMode=yes',str(src),f'{HOST}:{ROOT}/{rel}'],check=True)
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()

stamp=time.strftime('%Y%m%dT%H%M%S');backup=f'/var/backups/shuihu-assets/publish-{stamp}'
files=[f'generated/maps-v2/{s}/{m}.webp' for m in maps for s in STYLES]+[f'generated/maps-signage/{s}/{m}.svg' for m in maps for s in STYLES]+['data/catalog.json','data/generated-maps.json']+data
ssh(f"cd {ROOT} && for f in {' '.join(files)}; do [ -e \"$f\" ] && mkdir -p {backup}/$(dirname $f) && cp -a \"$f\" {backup}/$f; done; true")
with tempfile.TemporaryDirectory() as tmp:
  tmp=Path(tmp);pull('data/catalog.json',tmp/'catalog.json');catalog=json.loads((tmp/'catalog.json').read_text())
  signs=set(ssh(f"cd {ROOT}/generated/maps-signage && ls */*.svg 2>/dev/null").split())
  for m in maps:
    for s in STYLES:
      webp=DIST/f'generated/maps-v2/{s}/{m}.webp';push(webp,f'generated/maps-v2/{s}/{m}.webp');image_sha=sha(webp)
      if f'{s}/{m}.svg' in signs:
        svg=tmp/f'{s}-{m}.svg';pull(f'generated/maps-signage/{s}/{m}.svg',svg)
        text,n=re.subn(r'data:image/webp;base64,[A-Za-z0-9+/=]+','data:image/webp;base64,'+base64.b64encode(webp.read_bytes()).decode(),svg.read_text(),count=1)
        assert n==1,svg;svg.write_text(text);push(svg,f'generated/maps-signage/{s}/{m}.svg');image_sha=sha(svg)
      local=next((i for i in json.loads((DIST/'data/catalog.json').read_text())['items'] if i['id']==f'map-{m}-{s}'),{})
      for item in catalog['items']:
        if item['id']==f'map-{m}-{s}':
          item['sha256']=image_sha
          for k in ('status','productionState','width','height'):
            if k in local:item[k]=local[k]
  (tmp/'catalog.json').write_text(json.dumps(catalog,ensure_ascii=False));push(tmp/'catalog.json','data/catalog.json')
  generated=[i for i in catalog['items'] if i.get('category')=='maps' and i.get('generated')]
  (tmp/'generated-maps.json').write_text(json.dumps({'status':'awaiting-visual-review','count':len(generated),'items':generated},ensure_ascii=False));push(tmp/'generated-maps.json','data/generated-maps.json')
for rel in data:push(DIST/rel,rel)
ssh(f"chown -R 501:staff {ROOT}/generated/maps-v2 {ROOT}/generated/maps-signage {ROOT}/data")
print(json.dumps({'published':maps,'backup':backup,'data':data}))
