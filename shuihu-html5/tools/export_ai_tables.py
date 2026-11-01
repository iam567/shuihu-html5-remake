"""Export the AI / support tables into dist/data/battle.json.

supportPatterns: reach of heals, cures and 遁甲 (ROM 0x1509E): offsets from the caster, ending 0x12345678. Subtypes
  0x12/0x17/0x1A use 0xCC98, 0x13/0x18/0x1B use 0xCCD0, everyone else 0xCD38. Each includes the caster's own cell.
cursePatterns: reach of status curses (0xD148 / 0xD4CC): 0x1A uses 0xD21E, 0x1B uses 0xD252, others 0xD2B6.
aiClassBonus: target score bonus by class for the AI's attack choice (0x9192 reads table 0x91FE by target +0x21).
aiConfuseScore: 混乱 target score by subtype (table 0xD46E).
Usage: python3 tools/export_ai_tables.py ROM.bin
"""
import json,struct,sys
from pathlib import Path
rom=Path(sys.argv[1]).read_bytes();out=Path(__file__).resolve().parents[1]/'dist/data/battle.json'
s16=lambda o:struct.unpack('>h',rom[o:o+2])[0]
def pattern(p):
  cells=[]
  while struct.unpack('>I',rom[p:p+4])[0]!=0x12345678:cells.append([s16(p),s16(p+2)]);p+=4;assert len(cells)<80
  return cells
data=json.loads(out.read_text())
data['supportPatterns']={'small':pattern(0xCC98),'medium':pattern(0xCCD0),'large':pattern(0xCD38)}
data['cursePatterns']={'small':pattern(0xD21E),'medium':pattern(0xD252),'large':pattern(0xD2B6)}
data['aiClassBonus']=list(rom[0x91FE:0x920E])
data['aiConfuseScore']=list(rom[0xD46E:0xD48C])
p=data.setdefault('provenance',{})
p['supportPatterns']='ROM 0x1509E: 0xCC98 (subtypes 0x12/0x17/0x1A), 0xCCD0 (0x13/0x18/0x1B), 0xCD38 (others); offsets from the caster'
p['cursePatterns']='ROM 0xD148: 0xD21E (subtype 0x1A), 0xD252 (0x1B), 0xD2B6 (others)'
p['aiClassBonus']='ROM 0x91FE by target class, read at 0x91CC';p['aiConfuseScore']='ROM 0xD46E by subtype'
out.write_text(json.dumps(data,ensure_ascii=False,separators=(',',':')))
print({k:len(v) for k,v in data['supportPatterns'].items()},{k:len(v) for k,v in data['cursePatterns'].items()},data['aiClassBonus'],data['aiConfuseScore'])
