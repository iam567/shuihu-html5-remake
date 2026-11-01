from extract_graphics import *
import sys
src=Path(sys.argv[1]) if len(sys.argv)>1 else ROOT.parent/'runtime/captures/start_1264'
out=ROOT/'runtime'/src.name;out.mkdir(parents=True,exist_ok=True)
b=(src/'vram.bin').read_bytes();data=bytes(x for i in range(0,len(b),2) for x in (b[i+1],b[i]));reg=(src/'reg.bin').read_bytes();colors=struct.unpack('<64H',(src/'cram.bin').read_bytes());pal=[((c&7)*255//7,((c>>3)&7)*255//7,((c>>6)&7)*255//7) for c in colors]
for p in range(4):
 im=Image.new('RGBA',(256,512))
 for i in range(2048):im.paste(tile_image(data,i,pal,p<<13),(i%32*8,i//32*8))
 im.save(out/f'vram_tiles_palette{p}.png')
for name,off in [('plane_a',(reg[2]&0x38)<<10),('plane_b',(reg[4]&7)<<13)]:
 im=Image.new('RGBA',(512,256));words=struct.unpack('>2048H',data[off:off+4096])
 for i,a in enumerate(words):im.paste(tile_image(data,a&2047,pal,a,True),(i%64*8,i//64*8))
 im.save(out/(name+'.png'))
sprites=[];off=(reg[5]&0x7e)<<9;visited=set();n=0
while n not in visited and n<80:
 visited.add(n);y,size,attr,x=struct.unpack('>4H',data[off+n*8:off+n*8+8]);w=((size>>10)&3)+1;h=((size>>8)&3)+1;im=Image.new('RGBA',(w*8,h*8))
 for xx in range(w):
  for yy in range(h):im.paste(tile_image(data,(attr&2047)+xx*h+yy,pal,attr&0x6000,True),(xx*8,yy*8))
 if attr&0x800:im=im.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
 if attr&0x1000:im=im.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
 im.save(out/f'sprite_{n:02d}.png');sprites.append({'table_index':n,'tile':attr&2047,'palette':(attr>>13)&3,'x':(x&511)-128,'y':(y&511)-128,'width':w*8,'height':h*8,'attribute':attr});n=size&127
 if n==0:break
(out/'sprites.json').write_text(json.dumps(sprites,indent=2));print(sprites)
