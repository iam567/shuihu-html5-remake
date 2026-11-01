"""Export the cartridge's music choices into dist/data/music.json.

maps   - per map, the tune script opcode 0x4C ("back to this place's music", ROM 0x11FF2 sets FF6046) starts: routine
         0x27DC6 reads table 0x27E16 (one pointer per region, region = map id high byte, then one byte per map by its
         low byte) and sends it to the sound driver (0x1E41D4).
stages - per battle stage (FFE10F), the tune the battle starts with (0x10A88 / 0x1007E -> 0x27EBE, table 0x27EE4).
Usage: python3 tools/export_music.py ROM.bin
"""
import json,struct,sys
from pathlib import Path
rom=Path(sys.argv[1]).read_bytes();root=Path(__file__).resolve().parents[1]
assets=json.loads((root/'dist/data/assets.json').read_text())
maps={}
for m in assets['maps']:
  region,index=int(m['id'][:2],16),int(m['id'][2:],16)
  if not 1<=region<=12:continue
  p=struct.unpack('>I',rom[0x27E16+4*(region-1):0x27E1A+4*(region-1)])[0]
  maps[m['id']]=rom[p+index]
stages=list(rom[0x27EE4:0x27EE4+36])
out={'provenance':{'maps':'ROM 0x27DC6 / table 0x27E16 (opcode 0x4C)','stages':'ROM 0x27EBE / table 0x27EE4 by stage (FFE10F)'},'maps':maps,'stages':stages}
(root/'dist/data/music.json').write_text(json.dumps(out,ensure_ascii=False,separators=(',',':')))
from collections import Counter
print(len(maps),'maps',Counter(maps.values()),'stages',stages)
