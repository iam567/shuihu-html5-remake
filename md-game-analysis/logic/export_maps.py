from pathlib import Path
import struct,json,hashlib
r=Path(__file__).resolve().parents[1]; b=next((r/'baseline').glob('*.md')).read_bytes(); out=r/'logic'/'maps';out.mkdir(exist_ok=True)
u32=lambda p:struct.unpack_from('>I',b,p)[0]
def dec(p):
 start=p;res=bytearray();mode=0
 while p<len(b) and len(res)<65536:
  x=b[p];p+=1
  if x==0xf0:mode=0;continue
  if x==0xf1:mode=1;continue
  if x<=0xef:res.append(x);continue
  n=x&15
  if x==255:
   n=b[p];p+=1
   if n==0:return bytes(res),p
  q=b[p:p+mode+1];p+=mode+1;res.extend(q*n)
 raise ValueError((hex(start),len(res)))
groups=[u32(0x293ea+4*g) for g in range(13)];end=u32(groups[0]);rows=[]
for g,ptr in enumerate(groups):
 count=((groups[g+1] if g<12 else end)-ptr)//4
 for idx in range(count):
  p=u32(ptr+4*idx);start=p;layers=[]
  for layer in range(3):
   data,p=dec(p);f=out/f'{g:02x}_{idx:02x}_layer{layer}.bin';f.write_bytes(data);layers.append({'size':len(data),'file':f.name,'sha256':hashlib.sha256(data).hexdigest()})
  row={'id':f'{g:02x}{idx:02x}','group':g,'index':idx,'rom_start':start,'rom_end':p,'layers':layers}
  for key,table in [('tiles',0x32182),('metatiles',0x770a6),('palette',0xdd744)]:row[key]=u32(u32(table+g*4)+idx*4)
  rows.append(row)
(out/'maps.json').write_text(json.dumps(rows,ensure_ascii=False,indent=2));print('maps',len(rows));print([(x['id'],[y['size'] for y in x['layers']]) for x in rows])
# Spawn/location records have independent second-level indices, grouped by same high byte.
ps=[u32(0xde088+4*g) for g in range(13)];recs=[]
for g,p in enumerate(ps):
 endp=ps[g+1] if g<12 else 0xdeb4c
 # Last group ends at independently referenced table 0xDEB4C (code 0x182F8).
 if endp is None:continue
 for idx,a in enumerate(range(p,endp,16)):
  d=b[a:a+16]; recs.append({'id':f'{g:02x}{idx:02x}','rom':a,'width':d[0],'height':d[1],'layer1_width':d[2],'layer1_height':d[3],'camera_x':struct.unpack('b',d[4:5])[0],'camera_y':struct.unpack('b',d[5:6])[0],'player_x':int.from_bytes(d[6:8],'big'),'player_y':int.from_bytes(d[8:10],'big'),'direction':d[10],'animation':d[11],'unknown_12_15':d[12:].hex()})
(out/'spawn_records.json').write_text(json.dumps(recs,indent=2));print('spawn records',len(recs))
