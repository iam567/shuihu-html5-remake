"""Publish whole-map redraws (prepare_whole_maps.py) to the asset workshop as they come out of the generator.

Each run: pulls finished <map>-<style>.png from the VPS batch folders, paints the shop signs back (as
finalize_whole_maps.py does for the game), writes generated/maps-whole/<style>/<map>.webp, uploads the new or changed
ones and adds/updates catalog items "map-<id>-<style>-whole" in their own sidebar category per style
(maps-whole-<style>, created after "完整地图" when missing). Tile-assembled versions stay in the workshop for comparison. The server's own catalog.json and generated-maps.json are backed up and
merged item by item, as publish_workshop_maps.py does. check_whole_maps.py results, when present, go into each item.
Usage: python3 tools/publish_whole_maps.py BATCH ...     (run it again whenever more images are done)
Environment: SHUIHU_WORKSHOP (default root@130.94.65.16:/var/www/game-downloads/shz),
             SHUIHU_PRODUCTION (default root@130.94.65.16:/var/lib/shuihu-image-production).
"""
import hashlib,json,os,subprocess,sys,tempfile,time
from pathlib import Path
from PIL import Image
from finalize_whole_maps import paint_signs

ROOT=Path(__file__).resolve().parents[1];DIST=ROOT/'dist';QUALITY=85
LABELS={'ghibli':'吉卜力整图','hd2d':'HD-2D 光影整图'}   # styles chosen for the game
TARGET=os.environ.get('SHUIHU_WORKSHOP','root@130.94.65.16:/var/www/game-downloads/shz');HOST,WROOT=TARGET.split(':',1)
PROD=os.environ.get('SHUIHU_PRODUCTION','root@130.94.65.16:/var/lib/shuihu-image-production')
ssh=lambda cmd:subprocess.run(['ssh','-o','BatchMode=yes',HOST,cmd],check=True,capture_output=True,text=True).stdout
rsync=lambda *a:subprocess.run(['rsync','-a','--no-owner','--no-group','-e','ssh -o BatchMode=yes',*a],check=True)
sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()

if __name__=='__main__':
  rules=json.loads((DIST/'data/tile-rules.json').read_text())['maps'];signs=json.loads((DIST/'data/map-signs.json').read_text())['maps']
  state_path=DIST/'data/whole-map-publish.json';state=json.loads(state_path.read_text()) if state_path.exists() else {}
  fresh={};latest={}
  # Batches are given oldest first; the last batch holding a finished image of a map/style is the one published.
  for name in sys.argv[1:]:
    batch=ROOT/'production'/name
    rsync('--include=*.png','--include=status.json','--exclude=*',f'{PROD}/{name}/',f'{batch}/')
    check=json.loads((batch/'check.json').read_text()) if (batch/'check.json').exists() else {}
    for job in json.loads((batch/'jobs.json').read_text()):
      png=batch/'aligned'/f"{job['id']}.png"
      if not png.exists():png=batch/f"{job['id']}.png"
      if job['style'] in LABELS and png.exists():latest[f"{job['sourceId']}-{job['style']}"]=(name,job,png,check.get(job['id']))
  for key,(name,job,png,c) in latest.items():
      m,style=job['sourceId'],job['style']
      stamp=f'{name}:{png.name}:{png.stat().st_mtime_ns}:{json.dumps(c,sort_keys=True)}'
      if state.get(key,{}).get('stamp')==stamp:continue
      im=Image.open(png).convert('RGB');cell=job.get('cell') or im.width//rules[m]['width']
      if m in signs:paint_signs(im,signs[m]['signs'],cell/signs[m]['cell'])
      rel=f'generated/maps-whole/{style}/{m}.webp';out=DIST/rel;out.parent.mkdir(parents=True,exist_ok=True);im.save(out,'WEBP',quality=QUALITY,method=6)
      fresh[key]={'stamp':stamp,'rel':rel,'map':m,'style':style,'cell':cell,'size':im.size,'check':c,'batch':name}
  if not fresh:print(json.dumps({'published':0}));sys.exit()
  backup=f"/var/backups/shuihu-assets/publish-whole-{time.strftime('%Y%m%dT%H%M%S')}"
  ssh(f'cd {WROOT} && mkdir -p {backup}/data && cp -a data/catalog.json data/generated-maps.json {backup}/data/')
  for style in {f['style'] for f in fresh.values()}:
    ssh(f'mkdir -p {WROOT}/generated/maps-whole/{style}')
    files=[f"{f['map']}.webp" for f in fresh.values() if f['style']==style]
    rsync(*[str(DIST/f'generated/maps-whole/{style}/{x}') for x in files],f'{TARGET}/generated/maps-whole/{style}/')
  with tempfile.TemporaryDirectory() as tmp:
    tmp=Path(tmp);subprocess.run(['scp','-q','-o','BatchMode=yes',f'{TARGET}/data/catalog.json',str(tmp/'catalog.json')],check=True)
    catalog=json.loads((tmp/'catalog.json').read_text());items=catalog['items'];added=0
    for f in fresh.values():
      m,style=f['map'],f['style'];iid=f'map-{m}-{style}-whole'
      original=next(i for i in items if i['category']=='maps' and not i.get('generated') and i.get('details',{}).get('mapId')==m)
      c=f['check'];limit='整图一次重画，逻辑层不变；物件位置待逐格对齐检查。' if not c else (
        f"逐格检查：{c['judged']} 格中有 {c['boundaryFlagged']} 格在可走/阻挡交界处偏移（拼块版为 {c['tileVersionBoundaryFlagged']} 格）。")
      # Title prefix as the tile-assembled versions show it ("地图01-00"), falling back to the original's name.
      prefix=next((i['name'].split(' · ')[0] for i in items if i.get('generated') and i['category']=='maps' and i.get('details',{}).get('mapId')==m and ' · ' in i['name']),original['name'])
      item={'id':iid,'category':f'maps-whole-{style}','name':f"{prefix} · {LABELS[style]}",'image':f['rel'],
        'width':f['size'][0],'height':f['size'][1],'sourcePath':original.get('sourcePath'),'sha256':sha(DIST/f['rel']),'bytes':(DIST/f['rel']).stat().st_size,
        'confidence':{'level':'candidate','basis':'Whole map repainted in one image from the original map; logic layer unchanged','limit':limit},
        'details':original.get('details'),'bankId':original.get('bankId'),'generated':True,'style':style,'wholeMap':True,'cellPixels':f['cell'],
        'status':'whole-map-awaiting-review','productionState':'whole-map-candidate','check':c,'batch':f['batch']}
      if m in signs:item['signage']={'count':len(signs[m]['signs']),'state':'painted-from-reviewed-sign-layer','manifest':'data/signage-placements.json'}
      at=next((k for k,i in enumerate(items) if i['id']==iid),None)
      if at is not None:items[at]=item
      else:items.append(item);added+=1
    cats=catalog['categories']
    for style in LABELS:
      cid=f'maps-whole-{style}'
      if not any(c['id']==cid for c in cats):
        cats.insert(max(k for k,c in enumerate(cats) if c['id']=='maps' or c['id'].startswith('maps-whole-'))+1,{'id':cid,'name':LABELS[style],'count':0})
      if isinstance(catalog.get('notes'),dict):catalog['notes'][cid]=f'{LABELS[style]}：整张地图一次重画，招牌按原位置画回，逻辑层与原版逐格一致；每张附逐格对齐检查结果。'
    order={i['details']['mapId']:k for k,i in enumerate(items) if i['category']=='maps' and not i.get('generated')}
    whole=sorted((i for i in items if i['category'].startswith('maps-whole-')),key=lambda i:(i['category'],order.get(i['details']['mapId'],0)))
    items[:]=[i for i in items if not i['category'].startswith('maps-whole-')]+whole
    for c in cats:c['count']=sum(i['category']==c['id'] for i in items)
    catalog['totalItems']=len(items)
    (tmp/'catalog.json').write_text(json.dumps(catalog,ensure_ascii=False));rsync(str(tmp/'catalog.json'),f'{TARGET}/data/catalog.json')
    generated=[i for i in items if i.get('category','').startswith('maps') and i.get('generated')]
    (tmp/'generated-maps.json').write_text(json.dumps({'status':'awaiting-visual-review','count':len(generated),'items':generated},ensure_ascii=False));rsync(str(tmp/'generated-maps.json'),f'{TARGET}/data/generated-maps.json')
  ssh(f'chown -R 501:staff {WROOT}/generated/maps-whole {WROOT}/data')
  state.update(fresh);state_path.write_text(json.dumps(state,indent=1))
  print(json.dumps({'published':len(fresh),'added':added,'backup':backup}))
