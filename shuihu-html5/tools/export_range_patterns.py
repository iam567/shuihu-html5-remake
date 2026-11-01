"""Export the attack-range shapes into dist/data/battle.json (rangePatterns).

ROM 0xAEB2 holds 30 pointers, one per unit subtype (unit record +0x24, 1-based). Each points at (dx, dy) word pairs
ending with 0x12345678; the in-range test (0x4AB4 / 0x8BB4) accepts a target when target + (dx, dy) is the attacker's
cell, so each pair is the attacker's offset from the target. The weapon's own byte 2 (exported as range_candidate) is
not a distance: minus one it is the number of extra hits (0x49E4: when non-zero the attack runs again).
Usage: python3 tools/export_range_patterns.py ROM.bin
"""
import json,struct,sys
from pathlib import Path

rom=Path(sys.argv[1]).read_bytes();out=Path(__file__).resolve().parents[1]/'dist/data/battle.json'
s16=lambda o:struct.unpack('>h',rom[o:o+2])[0]
patterns=[]
for i in range(30):
  p=struct.unpack('>I',rom[0xAEB2+4*i:0xAEB6+4*i])[0];cells=[]
  while struct.unpack('>I',rom[p:p+4])[0]!=0x12345678:
    cells.append([s16(p),s16(p+2)]);p+=4
    assert len(cells)<64,(i,hex(p))
  patterns.append(cells)
data=json.loads(out.read_text())
data['rangePatterns']=patterns
data.setdefault('provenance',{})['rangePatterns']='ROM 0xAEB2: per-subtype (record +0x24) offsets attacker-minus-target, read by 0x4AB4/0x8BB4'
out.write_text(json.dumps(data,ensure_ascii=False,separators=(',',':')))
print(len(patterns),'patterns',[len(c) for c in patterns])
