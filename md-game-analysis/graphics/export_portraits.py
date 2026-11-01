from extract_graphics import *
from PIL import ImageDraw
out=ROOT/'portraits';out.mkdir(exist_ok=True);c=struct.unpack('<64H',(ROOT.parent/'runtime/captures/start_1264/cram.bin').read_bytes());pal=[((v&7)*255//7,((v>>3)&7)*255//7,((v>>6)&7)*255//7) for v in c];rows=[];unique={}
for i in range(78):
 a=struct.unpack_from('>I',rom,0x160000+i*4)[0];d=rom[a:a+1152];im=Image.new('RGBA',(48,48))
 for x in range(6):
  for y in range(6):im.paste(tile_image(d,x*6+y,pal,2<<13,True),(x*8,y*8))
 name=f'portrait_{i+1:02d}_{a:06x}.png';im.save(out/name);unique[a]=im
 rows.append({'portrait_id':i+1,'pointer_rom':hex(0x160000+i*4),'data_rom':hex(a),'width':48,'height':48,'tiles':36,'layout':'column-major 6x6 tiles','file':name,'palette_evidence':'runtime start_1264 palette2; Afu confirmed, other portraits unobserved'})
contact=Image.new('RGB',(8*104,((len(unique)+7)//8)*120),(40,40,40));draw=ImageDraw.Draw(contact)
for n,(a,im) in enumerate(unique.items()):
 x=n%8*104;y=n//8*120;im=im.resize((96,96),Image.Resampling.NEAREST);contact.paste(im,(x,y),im);draw.text((x,y+99),f'{a:06X}',fill='white')
contact.save(ROOT/'portraits_contact_sheet.png');(out/'index.json').write_text(json.dumps(rows,ensure_ascii=False,indent=2));print('entries',len(rows),'unique',len(unique))
