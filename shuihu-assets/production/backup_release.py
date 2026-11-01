import os,sys,json,urllib.request,urllib.parse,hashlib,base64,time,zipfile
from pathlib import Path
import importlib.util
spec=importlib.util.spec_from_file_location('vault', os.environ['SHUIHU_VAULT_HELPER']);v=importlib.util.module_from_spec(spec);spec.loader.exec_module(v)
base,opener,headers,csrf=v.connection()
if csrf:headers['X-CSRF-Token']=csrf
root=Path(__file__).resolve().parents[1]
receipt_path=root/'production/delivery-receipts.json'
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

if __name__=="__main__":
 path=Path(sys.argv[1]).resolve()
 parent=folder("水浒传素材重构");version=folder("补齐人物头像物品界面-20261029",parent)
 receipt["files"][path.name]=upload(path,version);persist();print("CMS SHA256 verified:",path.name)
