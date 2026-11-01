import sys,json,urllib.request,urllib.parse,hashlib,base64,time,zipfile
from pathlib import Path
import importlib.util,os
spec=importlib.util.spec_from_file_location('vault', os.environ['SHUIHU_VAULT_HELPER']);v=importlib.util.module_from_spec(spec);spec.loader.exec_module(v)
base,opener,headers,csrf=v.connection()
if csrf:headers['X-CSRF-Token']=csrf
root=Path(__file__).resolve().parent
receipt_path=root/'vault-receipt-town-styles-v1.json'
receipt=json.loads(receipt_path.read_text()) if receipt_path.exists() else {'project':'水浒传素材重构','files':{},'uploads':{}}
def persist():receipt_path.write_text(json.dumps(receipt,ensure_ascii=False,indent=2))
def req(action,data=None,**params):
 h=headers.copy();body=None
 if data is not None:h['Content-Type']='application/json';body=json.dumps(data).encode()
 r=urllib.request.Request(base+'/api.php?'+urllib.parse.urlencode({'action':action,**params}),data=body,headers=h)
 with opener.open(r,timeout=120) as response:return json.load(response)
def folder(name,parent=''):
 for e in req('list',parent=parent)['entries']:
  if e['name']==name and e['kind']=='folder':return e['id']
 return req('folder',{'name':name,'parent':parent})['id']
def upload(path,parent):
 digest=hashlib.sha256(path.read_bytes()).hexdigest()
 for e in req('list',parent=parent)['entries']:
  if e['name']==path.name:
   assert e['sha256']==digest,'Existing file differs; use a new version'
   return {'id':e['id'],'sha256':digest,'size':e['size'],'verified':True}
 state=receipt['uploads'].get(path.name)
 if not state:
  state=req('upload_init',{'parent':parent,'name':path.name,'size':path.stat().st_size});receipt['uploads'][path.name]=state;persist()
 off=int(req('upload_status',id=state['id'])['received'])
 with path.open('rb') as f:
  f.seek(off)
  while True:
   chunk=f.read(state['chunk_size'])
   if not chunk:break
   req('chunk',{'base64':base64.b64encode(chunk).decode()},id=state['id'],offset=off);off+=len(chunk)
 out=req('upload_finish',{'id':state['id'],'sha256':digest});assert out['sha256']==digest
 entry=next(e for e in req('list',parent=parent)['entries'] if e['id']==out['id']);assert entry['sha256']==digest and int(entry['size'])==path.stat().st_size
 return {**out,'verified':True}
archive=root/'水浒传-第一关室外三种画风-v1.zip'
with zipfile.ZipFile(archive,'w',zipfile.ZIP_DEFLATED) as z:
 for p in sorted((root/'dist/samples/town-styles-v1').rglob('*')):
  if p.is_file():z.write(p,p.relative_to(root/'dist/samples/town-styles-v1'))
parent=folder('水浒传素材重构');version=folder('第一关室外三种画风-20261029-v1',parent)
receipt.update(folderId=parent,versionFolderId=version,webUrl='https://game.areu.pro/shz/samples/town-styles-v1/')
for p in [archive,root/'dist/samples/town-styles-v1/pixel-hd.png',root/'dist/samples/town-styles-v1/unreal.png',root/'dist/samples/town-styles-v1/ghibli.png']:
 receipt['files'][p.name]=upload(p,version);persist();print('verified:',p.name,flush=True)
