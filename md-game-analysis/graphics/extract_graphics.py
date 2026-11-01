from pathlib import Path
from PIL import Image
import json,struct
ROOT=Path(__file__).resolve().parent
rom=(ROOT.parent/'baseline/水浒传 (繁) (川普科技)(16Mb).md').read_bytes()
def palette(off):
 return [(((v>>1)&7)*255//7,((v>>5)&7)*255//7,((v>>9)&7)*255//7) for v in struct.unpack('>64H',rom[off:off+128])]
def tiles(off):
 end=next(i for i in range(off,len(rom)-1,2) if rom[i:i+2]==b'\x34\x02')
 return rom[off:end],end
def tile_image(data,idx,pal,attr=0,transparent=False):
 im=Image.new('RGBA',(8,8)); px=im.load()
 chunk=data[idx*32:idx*32+32].ljust(32,b'\x00')
 for y in range(8):
  for x in range(8):
   c=(chunk[y*4+x//2]>>(4 if x%2==0 else 0))&15
   xx=7-x if attr&0x800 else x; yy=7-y if attr&0x1000 else y
   px[xx,yy]=pal[((attr>>13)&3)*16+c]+(0 if transparent and c==0 else 255,)
 return im
def map_image(off,w,h,data,pal,name):
 words=struct.unpack('>'+str(w*h)+'H',rom[off:off+w*h*2]); im=Image.new('RGBA',(w*8,h*8))
 for i,v in enumerate(words): im.paste(tile_image(data,v&2047,pal,v,True),((i%w)*8,(i//w)*8))
 im.save(ROOT/(name+'.png')); (ROOT/(name+'.json')).write_text(json.dumps({'rom_offset':hex(off),'width_tiles':w,'height_tiles':h,'words':list(words)},ensure_ascii=False))
 return {'name':name,'rom_offset':hex(off),'width_tiles':w,'height_tiles':h,'max_tile_index':max(v&2047 for v in words)}
def atlas(data,pal,p,name):
 n=len(data)//32; im=Image.new('RGBA',(256,((n+31)//32)*8))
 for i in range(n): im.paste(tile_image(data,i,pal,p<<13),(i%32*8,i//32*8))
 im.save(ROOT/(name+'.png'))
if __name__=='__main__':
 pal=palette(0x29344); t,end=tiles(0x9fe38); data=bytes(32)+t
 for p in range(4): atlas(data,pal,p,'opening_tiles_palette_'+str(p))
 entries=[]
 for a,w,h,n in [(0xdac96,40,64,'opening_background_40x64'),(0xdc4c2,31,10,'title_overlay'),(0x27ca6,12,3,'menu_option_1'),(0x27d7e,12,3,'menu_option_2')]:entries.append(map_image(a,w,h,data,pal,n))
 thumb=Image.new('RGB',(320,224)); bg=Image.open(ROOT/'opening_background_40x64.png'); thumb.paste(bg,(0,0),bg); ov=Image.open(ROOT/'title_overlay.png');thumb.paste(ov,(32,24),ov)
 for a,n,y in [(0x27ca6,'menu_option_1',128),(0x27d7e,'menu_option_2',160)]:
  im=Image.open(ROOT/(n+'.png'));thumb.paste(im,(104,y),im)
 thumb.save(ROOT/'title_reconstructed.png')
 (ROOT/'index.json').write_text(json.dumps({'tile_bank':{'start':hex(0x9fe38),'end_exclusive':hex(end),'tiles':len(t)//32,'vram_first_tile':1},'palette_rom_offset':'0x29344','maps':entries,'limitations':'Static reconstruction; dynamic scroll/fades and sprite overlays not represented.'},ensure_ascii=False,indent=2))
