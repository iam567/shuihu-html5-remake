from extract_graphics import *
from PIL import ImageDraw
out=ROOT/'fonts';out.mkdir(exist_ok=True);rows=[];total=0
for bank in range(8):
 start=struct.unpack_from('>I',rom,0xae2a4+bank*4)[0];end=struct.unpack_from('>I',rom,0xae2a4+(bank+1)*4)[0] if bank<7 else 0xbc6e4;n=(end-start)//32;sheet=Image.new('RGB',(16*40,((n+15)//16)*48),'white');draw=ImageDraw.Draw(sheet)
 for c in range(n):
  raw=rom[start+c*32:start+(c+1)*32];im=Image.new('RGBA',(16,16),(255,255,255,0));pix=im.load()
  for t in range(4):
   for y in range(8):
    for x in range(8):
     if raw[t*8+y]&(128>>x):pix[t%2*8+x,t//2*8+y]=(0,0,0,255)
  im.save(out/f'bank{bank}_{c:02x}.png');xx=c%16*40;yy=c//16*48;sheet.paste(im.resize((32,32),Image.Resampling.NEAREST),(xx,yy),im.resize((32,32),Image.Resampling.NEAREST));draw.text((xx,yy+33),f'{c:02X}',fill='black')
 sheet.save(out/f'bank{bank}_sheet.png');rows.append({'bank':bank,'start':hex(start),'end':hex(end),'glyph_count':n,'encoding':'bank command F0+bank, then byte code00..EF; no Unicode mapping yet','layout':'four 8x8 1bpp tiles, row major; MSB first'});total+=n
(out/'index.json').write_text(json.dumps(rows,ensure_ascii=False,indent=2));print('glyphs',total)
