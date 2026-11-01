from pathlib import Path
import json
r=Path(__file__).resolve().parents[1];b=next((r/'baseline').glob('*.md')).read_bytes();o=r/'logic'
ops=json.loads((o/'script_opcodes.json').read_text());spawners={x['opcode'] for x in ops if x['handler'] in ['01011e','011e2a']}
def decode(p):
 d=b[p:p+64]
 return {'rom':p,'sprite_type':d[0],'animation':d[1],'x':int.from_bytes(d[2:4],'big'),'y':int.from_bytes(d[4:6],'big'),'direction':d[6],'portrait_or_identity':d[7],'skill_slots_08_0b':list(d[8:12]),'status_0c_0f':list(d[12:16]),'level':d[16],'experience':d[17],'hp':int.from_bytes(d[18:20],'big'),'stats_14_1a':list(d[20:27]),'movement_1b':d[27],'max_hp':int.from_bytes(d[30:32],'big'),'class':d[33],'subtype':d[36],'equipment_ids':list(d[38:42]),'passive_item':d[42],'uses':list(d[43:47]),'raw':d.hex()}
initial=[decode(0x1536+i*64) for i in range(30)]
(o/'initial_30_units.json').write_text(json.dumps(initial,indent=2));candidates=[]
for p in range(0xe2e16,0x100000-68,2):
 op=int.from_bytes(b[p:p+2],'big');slot=int.from_bytes(b[p+2:p+4],'big')
 if op not in spawners or slot>=30:continue
 d=decode(p+4)
 if not(0<d['sprite_type']<128 and d['x']%32==0 and d['y']%32==0 and d['x']<4096 and d['y']<4096 and 0<d['level']<100 and d['class']<15 and 0<d['subtype']<=30):continue
 d.update({'opcode':op,'slot_search_start':slot,'evidence':'script byte-pattern plus record-structure validation; unverified reachability'})
 candidates.append(d)
(o/'script_unit_candidates.json').write_text(json.dumps(candidates,indent=2));print('initial 30 records;',len(candidates),'script spawn candidates')
