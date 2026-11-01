from pathlib import Path
import json
root=Path(__file__).resolve().parents[2]; src=root/'md-game-analysis'; b=next((src/'baseline').glob('*.md')).read_bytes(); u16=lambda p:int.from_bytes(b[p:p+2],'big');u32=lambda p:int.from_bytes(b[p:p+4],'big')
banks=json.loads((src/'logic/script_entrypoints.json').read_text()); start=0xe2e16;end=0xee2d0
maps=json.loads((src/'logic/maps/maps.json').read_text()); npcs={}
for m in maps:
 mid=int(m['id'],16);p=u32(u32(0xdc9d0+4*(mid>>8))+4*(mid&255));rows=[]
 while b[p] and len(rows)<8:
  raw=list(b[p:p+16]);rows.append({'slot':8+len(rows),'characterId':raw[0],'animationState':raw[1],'x':u16(p+2),'y':u16(p+4),'movementByte':raw[6],'byte7':raw[7],'active':True,'raw':raw});p+=16
 npcs[m['id']]=rows
# Stage 0 default mandatory deployment and enemy scenario records, not demo/init records.
first=[]
for slot,identity in enumerate([1,3]):
 p=0x176ea+(identity-1)*16;r=list(b[p:p+16]);v=[0]*64
 v[0]=r[0];v[1]=4;v[2:6]=b[0x24a98+slot*4:0x24a9c+slot*4];v[6]=1;v[7]=r[1];v[8:12]=r[2:6];v[16:18]=r[6:8];v[36]=r[8];v[42]=r[9];v[38:42]=r[10:14];v[33]=r[14]
 for j,item in enumerate(v[38:42]):v[43+j]=b[0x28e54+(item-1)*8+1] if item else 0
 first.append({'slot':slot,'raw':v,'team':'player'})
for i in range(b[0x1ca1b]):first.append({'slot':12+i,'raw':list(b[0x1ca1c+i*64:0x1ca1c+(i+1)*64]),'team':'enemy'})
for unit in first:unit['raw'][27]=b[0x14d8c+unit['raw'][36]-1]
out={'formatVersion':1,'description':'Original event bytecode only; interpreted as game commands, never 68000 instructions. Addresses retained for source auditing.','base':start,'bytes':list(b[start:end]),'banks':[{'group':x['group'],'entries':[e['address']-start if start<=e['address']<end and e['address'] not in {k['base'] for k in banks} else None for e in x['entries']]} for x in banks],'firstBattle':{'units':first,'evidence':'mandatory party 249F2; coordinates24A98; persistent176EA; scenario1CA1A; stats recalculated14C80','optionalDeploymentRestored':False},'npcs':npcs,'shops':[list(b[u32(0x1b562+4*i)+1:u32(0x1b562+4*i)+1+b[u32(0x1b562+4*i)]]) for i in range(12)],'prices':[u16(0x1b418+2*i) for i in range(143)],'npcMasks':{str(u16(0x18232+2*i)):u16(0x1828c+2*i) for i in range(15)},'battleGold':[u32(0x11adc+i*4) for i in range(36)],'moneyRewards':[u32(0x1aab2+i*4) for i in range(10)],'spawns':json.loads((src/'logic/maps/spawn_records.json').read_text())}
(root/'shuihu-html5/dist/data/story.json').write_text(json.dumps(out,separators=(',',':')))

hidden=root/'shuihu-html5/dist/data/hidden-items.json'
if hidden.exists():
 out['hiddenItems']=json.loads(hidden.read_text())['items']
 (root/'shuihu-html5/dist/data/story.json').write_text(json.dumps(out,separators=(',',':')))
