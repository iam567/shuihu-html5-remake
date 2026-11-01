"""Export who may equip or carry each item into dist/data/battle.json (equipMasks).

ROM 0x1A130 holds one 32-bit mask per item id (0..142): bit n set = subtype n+1 may use it. The equipment screen
(0x1A0DC) tests it against the persistent record's subtype (+8), the shop (0x1B6E8) marks who can use the item.
Usage: python3 tools/export_equip_masks.py ROM.bin
"""
import json,struct,sys
from pathlib import Path
rom=Path(sys.argv[1]).read_bytes();out=Path(__file__).resolve().parents[1]/'dist/data/battle.json'
data=json.loads(out.read_text())
data['equipMasks']=[struct.unpack('>I',rom[0x1A130+4*i:0x1A134+4*i])[0] for i in range(143)]
data.setdefault('provenance',{})['equipMasks']='ROM 0x1A130: 32-bit mask per item id, bit = subtype-1 (tested at 0x1A0DC, shop 0x1B6E8)'
out.write_text(json.dumps(data,ensure_ascii=False,separators=(',',':')))
m=data['equipMasks'];print('carried 128-139 all-ones?',[hex(m[i]) for i in range(128,143)]);print('accessories',[hex(m[i]) for i in range(112,124)])
