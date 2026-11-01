"""Export per-stage battle deployment tables for the 36 battles into dist/data/battle-stages.json.

Sources (ROM addresses, all indexed by stage number FFE10F):
  0x1C98A  scenario pointer: [first non-player slot, unit count, count x 64-byte unit records] (loader 0x1C898)
  0x24962  mandatory party members, 0xFF-terminated (0x248E2)
  0x24A08  coordinates for the mandatory members, x/y words in 1/32 tile (0x24B60)
  0x24B3C  maximum deployed party size (0x248E2)
  0x14200  41 (dx,dy) offsets around slot 0 for members without fixed coordinates (0x24C1A)
  0x176EA  20 x 16-byte initial persistent character records (copied to FFE630 by 0x17698)
  0x28E54  item table, byte 1 of each 8-byte entry is the use count put in unit bytes 43-46
  0x14D8C  movement by subtype, written to unit byte 27
"""
import json,struct
from pathlib import Path

root=Path(__file__).resolve().parents[2]
b=next((root/'md-game-analysis/baseline').glob('*.md')).read_bytes()
u32=lambda a:struct.unpack('>I',b[a:a+4])[0];u16=lambda a:struct.unpack('>H',b[a:a+2])[0]
stages=[]
for stage in range(36):
  p=u32(0x1c98a+4*stage);first,count=b[p],b[p+1]
  units=[{'slot':first+i,'raw':list(b[p+2+i*64:p+2+(i+1)*64])} for i in range(count)]
  q=u32(0x24962+4*stage);mandatory=[]
  while b[q]!=0xff:mandatory.append(b[q]);q+=1
  c=u32(0x24a08+4*stage)
  stages.append({'stage':stage,'firstSlot':first,'units':units,'mandatory':mandatory,
    'coordinates':[{'x':u16(c+4*i),'y':u16(c+4*i+2)} for i in range(len(mandatory))],'maxDeploy':b[0x24b3c+stage],
    'source':{'scenario':hex(p),'mandatory':hex(u32(0x24962+4*stage)),'coordinates':hex(c)}})
out={'formatVersion':1,
  'description':'Original battle deployment tables by stage. Player records are built from persistent 16-byte character records; scenario records are copied to unit slots firstSlot.. as in ROM 0x1C898.',
  'stages':stages,
  'roster':[list(b[0x176ea+i*16:0x176ea+(i+1)*16]) for i in range(20)],
  'placementOffsets':[list(struct.unpack('>hh',b[0x14200+4*i:0x14204+4*i])) for i in range(41)],
  'itemUses':[0]+[b[0x28e54+(item-1)*8+1] for item in range(1,143)],
  'movementBySubtype':[0]+[b[0x14d8c+i] for i in range(64)]}
target=root/'shuihu-html5/dist/data/battle-stages.json'
target.write_text(json.dumps(out,separators=(',',':')))
print(json.dumps({'stages':len(stages),'scenarioUnits':sum(len(s['units']) for s in stages),'bytes':target.stat().st_size}))
