"""Export each battle stage's 戰鬥目的 (victory / defeat conditions) into dist/data/objectives.json.

The battle system menu's 戰鬥目的 (ROM strings from 0x1A923) reads two string pointers per stage from 0x1A73C (8 bytes
per stage: victory, defeat). Text bytes: 0xF0-0xF4 select font bank 0-4, 0xFF ends. A few glyph codes are read wrong by
unicode.json, so those stages take the text the cartridge shows on screen (checked in the emulator: stages 17, 23, 30, 35).
Usage: python3 tools/export_objectives.py ROM.bin
"""
import json,struct,sys
from pathlib import Path
rom=Path(sys.argv[1]).read_bytes();root=Path(__file__).resolve().parents[1]
glyphs=json.loads((root/'dist/data/unicode.json').read_text())['glyphs']
def text(a):
  out,bank='',0
  while rom[a]!=0xFF:
    x=rom[a];a+=1
    if 0xF0<=x<=0xF4:bank=x-0xF0
    else:out+=glyphs.get(f'{bank}:{x}','□')
  return out
SEEN={17:('晁蓋趕到西方出口',None),23:('拿到玲瓏古玉',None),30:('打敗高俅',None),35:('高俅亡',None)}
stages=[]
for i in range(36):
  win,lose=struct.unpack('>II',rom[0x1A73C+8*i:0x1A744+8*i])
  w,l=text(win),text(lose)
  if i in SEEN:w=SEEN[i][0] or w
  stages.append({'victory':w.strip(),'defeat':[x for x in l.split() if x]})
assert not any('□' in s['victory']+''.join(s['defeat']) for s in stages),[s for s in stages if '□' in s['victory']]
(root/'dist/data/objectives.json').write_text(json.dumps({'provenance':'ROM 0x1A73C (two string pointers per stage), strings 0x1A923+','stages':stages},ensure_ascii=False,separators=(',',':')))
for i,s in enumerate(stages):print(i,s['victory'],'|','、'.join(s['defeat']))
