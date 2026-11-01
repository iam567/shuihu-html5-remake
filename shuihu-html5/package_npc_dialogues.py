from pathlib import Path
import sys,json,struct,ast
P=Path(__file__).resolve().parent;SRC=P.parent/'md-game-analysis';sys.path.insert(0,str(SRC/'graphics'))
from extract_graphics import ROOT,rom
from PIL import Image,ImageDraw
# Reuse the decoded-font renderer without running its main export side effects.
src=ast.parse((SRC/'graphics/export_text.py').read_text());tree=ast.Module(body=[n for n in src.body if isinstance(n,ast.FunctionDef)],type_ignores=[]);exec(compile(tree,'export_text.py','exec'))
out=P/'dist/assets/npc-dialogues';out.mkdir(parents=True,exist_ok=True);top=list(struct.unpack('>186I',rom[0xdeb4c:0xdee34]));starts=sorted(set(top));ids=[];ptrs=set()
for i,a in enumerate(top):
 end=starts[starts.index(a)+1] if a!=starts[-1] else 0xdf140;vs=list(struct.unpack('>'+str((end-a)//4)+'I',rom[a:end]));ids.append({'identity':i,'variantPointerOffset':hex(a),'variants':[f'{v:06x}' if v else None for v in vs]});ptrs.update(v for v in vs if v)
entries=[]
for a in sorted(ptrs):
 i=a;count=0
 while i<len(rom) and count<20000:
  x=rom[i];i+=1;count+=1
  if x==0xfd:i+=1
  elif x==0xff:
   flag=rom[i];i+=1
   if flag!=0xff:break
 raw=rom[a:i];ts=tokens_for(raw,True)
 if ts and ts[0]['type']=='portrait':ts[0]['type']='npc_identity'
 name=f'{a:06x}';rel=f'assets/npc-dialogues/{name}.png';render(ts,f'NPC / ROM {a:06X}',P/'dist'/rel);entries.append({'id':name,'image':rel,'rawHex':raw.hex(),'tokens':ts,'endingFlag':flag,'endingMeaning':'end' if flag==0 else 'invoke_same_map_script','scriptId':None if flag==0 else flag})
manifest={'formatVersion':1,'portraitSource':'interacting actor.characterId; initial text byte is identity, not portrait','identitySource':'actor byte7','variantSource':'FFE300[identity]','identities':ids,'dialogues':entries,'evidence':'DEB4C 186-entry identity table; subtable boundaries from next pointer; zero variant pointers preserved; FF ending flag FF=continue,00=end,other=scriptId'};(P/'dist/data/npc-dialogues.json').write_text(json.dumps(manifest,ensure_ascii=False,separators=(',',':')))
known={r['id'] for r in entries};assert all(v is None or v in known for r in ids for v in r['variants']);assert all((P/'dist'/r['image']).is_file() for r in entries)
print('identities',len(ids),'dialogs',len(entries),'afu',ids[61])
