from extract_graphics import *
from PIL import ImageDraw
out=ROOT/'characters';out.mkdir(exist_ok=True);c=struct.unpack('<64H',(ROOT.parent/'runtime/captures/start_1264/cram.bin').read_bytes());pal=[((v&7)*255//7,((v>>3)&7)*255//7,((v>>6)&7)*255//7) for v in c];ptrs=list(struct.unpack('>79I',rom[0x100000:0x10013c]));unique=sorted(set(ptrs));rows=[];thumbs=[]
for i,a in enumerate(unique):
 end=unique[i+1] if i+1<len(unique) else 0x153400;n=(end-a)//512;sheet=Image.new('RGBA',(32*n,32))
 for f in range(n):
  d=rom[a+f*512:a+(f+1)*512];im=Image.new('RGBA',(32,32))
  for x in range(4):
   for y in range(4):im.paste(tile_image(d,x*4+y,pal,2<<13,True),(x*8,y*8))
  im.save(out/f'{a:06x}_frame{f:02d}.png');sheet.paste(im,(32*f,0))
 sheet.save(out/f'{a:06x}_sheet.png');thumbs.append((a,sheet.crop((0,0,32,32))))
 rows.append({'start':hex(a),'end':hex(end),'character_ids':[i for i,v in enumerate(ptrs) if v==a],'frame_count_by_pointer_boundary':n,'frame_size_bytes':512,'frame_size_pixels':[32,32],'layout':'4x4 tiles column-major','palette_evidence':'runtime start_1264 palette2; other contexts unverified','boundary_note':'last bank endpoint 0x153400 inferred from 0xFF padding'})
contact=Image.new('RGB',(12*80,((len(thumbs)+11)//12)*88),(50,50,50));draw=ImageDraw.Draw(contact)
for i,(a,im) in enumerate(thumbs):
 x=i%12*80;y=i//12*88;im=im.resize((64,64),Image.Resampling.NEAREST);contact.paste(im,(x,y),im);draw.text((x,y+66),f'{a:06X}',fill='white')
contact.save(ROOT/'characters_contact_sheet.png');(out/'index.json').write_text(json.dumps(rows,indent=2));print('banks',len(rows),'frames',sum(r['frame_count_by_pointer_boundary'] for r in rows))
