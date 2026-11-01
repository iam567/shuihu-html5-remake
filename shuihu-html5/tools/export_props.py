"""Export the map props (opcode 0x3D) and the cut-scene emotes (opcodes 0x2E / 0x2F / 0x30) from the ROM.

Props: table 0x25F86 holds 32 entries (map word, x, y, sprite pattern); bit n of FFE11C (starts 0x243, flipped by opcode
0x3D) shows entry n while its map is loaded (0x25F02). Their tiles are loaded per map by 0x25D46 (graphics address, VRAM
tile); entries for maps with no loader (09xx, 0A04, 0F07, 14xx: not in the game) are left out.
Emotes: tiles 0x9087A loaded at VRAM tile 0x500 (opcode handlers 0x115A2 / 0x1160A / 0x11672); patterns 0x6B-0x74.
A pattern is a list at 0x28188 of hardware sprites (y, size, attr, x); attr gives tile, palette line and flips.
Palette line 2 (people) is the one the game keeps for sprites (taken from the running game in 晁家庄); line 1 is the
map's own (table 0xDD744, 32 colours per map) and line 3 the cart palette 0x260C8 that 0x26086 loads on 0206 / 0708.
Writes dist/assets/props/*.png and dist/data/props.json. Usage: python3 tools/export_props.py ROM.bin
"""
import json,struct,sys
from pathlib import Path
from PIL import Image
rom=Path(sys.argv[1]).read_bytes();root=Path(__file__).resolve().parents[1];out=root/'dist/assets/props';out.mkdir(parents=True,exist_ok=True)
u32=lambda a:struct.unpack('>I',rom[a:a+4])[0];u16=lambda a:struct.unpack('>H',rom[a:a+2])[0];s16=lambda a:struct.unpack('>h',rom[a:a+2])[0]
LINE2=[0,0,511,311,39,10,29,488,458,55,6,48,24,438,292,146]   # 9-bit BBBGGGRRR, palette line 2 in the running game
LOAD={0x206:(0x90CFC,0x4A0),0x307:(0x92444,0x4F4),0x308:(0x925C6,0x4EC),0x708:(0x92848,0x4E8),0x808:(0x92B4A,0x4DC),
  0x809:(0x92FCC,0x300),0x80A:(0x925C6,0x300),0xA06:(0x925C6,0x4EC),0xA07:(0x9324E,0x4C0),0xA08:(0x9324E,0x4C0),
  0xB0A:(0x939D0,0x4E0),0xC04:(0x93DD2,0x4E0),0x404:(0x92444,0x100)}   # 0x25D46
def rgb9(w):return ((w&7)*36,((w>>3)&7)*36,((w>>6)&7)*36,255)
def map_palette(mp):
  p=u32(u32(0xDD744+(mp>>8)*4)+(mp&255)*4);return [(((w>>1)&7)*36,((w>>5)&7)*36,((w>>9)&7)*36,255) for w in (u16(p+2*k) for k in range(64))]
LINE3={0x206:0x260C8,0x708:0x260C8}   # 0x26086: carts on 0206 / 0708 get palette line 3 from 0x260C8
def palette(mp):
  # A map palette is 32 colours, lines 0-1 (0x2D00); the 32 after it belong to the next map.
  pal=(map_palette(mp)[:32] if mp is not None else [(0,0,0,255)]*32)+[rgb9(w) for w in LINE2]+[(0,0,0,0)]*16
  if mp in LINE3:pal[48:64]=[(((w>>1)&7)*36,((w>>5)&7)*36,((w>>9)&7)*36,255) for w in (u16(LINE3[mp]+2*k) for k in range(16))]
  return pal
def tiles(addr,base):
  n=0
  while u16(addr+2*n)!=0x3402:n+=1
  data=rom[addr:addr+2*n];return {base+t:data[t*32:t*32+32] for t in range(len(data)//32)}
def compose(pattern,vram,pal):
  a=u32(0x28188+4*(pattern&0x1fff));pieces=[]
  for k in range(u16(a)+1):
    e=a+2+8*k;size=u16(e+2);pieces.append((s16(e+6),s16(e),((size>>10)&3)+1,((size>>8)&3)+1,u16(e+4)))
  ox=min(p[0] for p in pieces);oy=min(p[1] for p in pieces)
  im=Image.new('RGBA',(max(p[0]+p[2]*8 for p in pieces)-ox,max(p[1]+p[3]*8 for p in pieces)-oy),(0,0,0,0))
  for x,y,w,h,attr in pieces:
    tile,line,hf,vf=attr&0x7ff,(attr>>13)&3,bool(attr&0x800),bool(attr&0x1000)
    for cx in range(w):
      for cy in range(h):
        tb=vram[tile+cx*h+cy];cell=Image.new('RGBA',(8,8),(0,0,0,0))
        for yy in range(8):
          for xx in range(8):
            v=(tb[yy*4+xx//2]>>(4*(1-xx%2)))&15
            if v:cell.putpixel((7-xx if hf else xx,7-yy if vf else yy),pal[line*16+v])
        im.alpha_composite(cell,(x-ox+(w-1-cx if hf else cx)*8,y-oy+(h-1-cy if vf else cy)*8))
  return im,ox,oy
props=[]
for n in range(32):
  a=0x25F86+8*n;mp,x,y,pat=u16(a),u16(a+2),u16(a+4),u16(a+6)
  if mp not in LOAD:continue
  im,ox,oy=compose(pat,tiles(*LOAD[mp]),palette(mp));name=f'prop-{n:02d}.png';im.save(out/name)
  props.append({'bit':n,'map':f'{mp:04x}','x':x,'y':y,'pattern':pat,'image':f'assets/props/{name}','dx':ox,'dy':oy,'w':im.width,'h':im.height})
emote_tiles=tiles(0x9087A,0x500);emotes={}
for pat in range(0x6B,0x75):
  im,ox,oy=compose(pat,emote_tiles,palette(None));name=f'emote-{pat:02x}.png';im.save(out/name)
  emotes[f'{pat:02x}']={'image':f'assets/props/{name}','dx':ox,'dy':oy,'w':im.width,'h':im.height}
(root/'dist/data/props.json').write_text(json.dumps({'provenance':'ROM 0x25F86 props (FFE11C starts 0x243), loader 0x25D46, emotes 0x9087A @ tile 0x500, patterns 0x28188','initialMask':0x243,'props':props,'emotes':emotes},ensure_ascii=False,indent=1))
print(len(props),'props',[(p['bit'],p['map']) for p in props],len(emotes),'emote frames')
