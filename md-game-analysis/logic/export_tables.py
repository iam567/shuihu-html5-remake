from pathlib import Path
import json,csv
r=Path(__file__).resolve().parents[1];b=next((r/'baseline').glob('*.md')).read_bytes();o=r/'logic';u32=lambda p:int.from_bytes(b[p:p+4],'big')
fields=['max_hp_1e','attack0_14','attack1_15','defense0_16','defense1_17','critical_18','hit_19','resist_1a']
growth=[]
for c in range(15):
 p=u32(0x14daa+4*c);stats=[]
 for i,f in enumerate(fields):
  t=b[p+i*4:p+i*4+4];stats.append({'field':f,'base':t[0],'numerator':t[1],'denominator':t[2],'cap':t[3]})
 growth.append({'class_index':c,'rom':p,'stats':stats})
(o/'class_growth.json').write_text(json.dumps(growth,indent=2))
with (o/'class_growth_levels_1_99.csv').open('w') as f:
 w=csv.writer(f);w.writerow(['class_index','level']+fields)
 for g in growth:
  for lev in range(1,100):w.writerow([g['class_index'],lev]+[min(x['cap'],x['base']+(lev-1)*x['numerator']//x['denominator']) for x in g['stats']])
trans=[]
for c in range(15):
 p=u32(0x5f24+4*c);pairs=[]
 for k in range(20):
  v,lev=b[p+2*k:p+2*k+2];pairs.append({'subtype':v,'transition_at_level':lev,'next_subtype':None if lev==100 else b[p+2*k+2]})
  if lev==100:break
 trans.append({'class':c,'rom':p,'pairs':pairs})
(o/'class_progression.json').write_text(json.dumps(trans,indent=2))
rows=[]
for i in range(142):
 p=0x28e54+i*8;t=list(b[p:p+8]);rows.append({'id':i+1,'rom':p,'power_or_quantity':t[0],'initial_uses':t[1],'range_candidate':t[2],'unknown3':t[3],'unknown4':t[4],'unknown5':t[5],'hit_bonus':t[6],'effect_type':t[7],'all_zero':not any(t)})
(o/'skills_items_142.json').write_text(json.dumps(rows,indent=2))
with (o/'skills_items_142.csv').open('w') as f:
 w=csv.DictWriter(f,fieldnames=rows[0].keys());w.writeheader();w.writerows(rows)
rows=[]
for i in range(177):
 p=0x1d84b6+i*4;t=list(b[p:p+4]);row={'id':i,'rom':p,'raw':t}
 if t[0]&128:row.update({'route':'z80','mailbox_A00020':t[1],'mailbox_A00022':t[2]})
 else:
  ind=t[1]&127;row.update({'route':'psg','channel_index':t[0]>>4,'priority':t[0]&15,'sequence_id':ind,'sequence_pointer':u32(0x1d877a+ind*4) if ind<122 else None})
 rows.append(row)
(o/'sound_command_routes.json').write_text(json.dumps(rows,indent=2))
print('15 growth classes, 1485 level rows, 142 skills/items, 177 sound routes')
