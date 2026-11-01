from extract_graphics import *
from PIL import ImageDraw
rs=json.loads((ROOT.parent/'logic/maps/maps.json').read_text());bankout=ROOT/'map_banks';bankout.mkdir(exist_ok=True);banks={}
for r in rs:
 if not r['layers'][1]['size']:continue
 k=(r['tiles'],r['metatiles'],r['palette']);banks.setdefault(k,{'maps':[],'ids':set()});banks[k]['maps'].append(r['id']);banks[k]['ids'].update((ROOT.parent/'logic/maps'/r['layers'][1]['file']).read_bytes())
index=[]
for k,v in banks.items():
 t,m,p=k;name=f'{t:06x}_{m:06x}';d,end=tiles(t);vram=bytes(0x200*32)+d;pal=palette(p);im=Image.new('RGBA',(512,((max(v['ids'])+16)//16)*32));words={}
 for n in sorted(v['ids']):
  ws=struct.unpack('>16H',rom[m+n*32:m+n*32+32]);words[n]=list(ws)
  for j,x in enumerate(ws):im.paste(tile_image(vram,x&2047,pal,x),(n%16*32+j%4*8,n//16*32+j//4*8))
 im.save(bankout/(name+'_metatiles.png'));(bankout/(name+'_tiles.bin')).write_bytes(d)
 for pp in range(2):
  a=Image.new('RGBA',(256,((len(d)//32+31)//32)*8))
  for i in range(len(d)//32):a.paste(tile_image(d,i,pal,pp<<13),(i%32*8,i//32*8))
  a.save(bankout/(name+f'_tiles_palette{pp}.png'))
 entry={'name':name,'tiles_rom':hex(t),'tiles_end':hex(end),'tile_count':len(d)//32,'vram_first_tile':512,'metatiles_rom':hex(m),'palette_rom':hex(p),'palette_rgb':pal[:32],'maps':v['maps'],'metatile_words':words};index.append(entry)
(bankout/'index.json').write_text(json.dumps(index,ensure_ascii=False,indent=2))
files=sorted((ROOT/'maps').glob('*.png'));cw,ch=220,190;contact=Image.new('RGB',(cw*6,ch*((len(files)+5)//6)),(30,30,30));draw=ImageDraw.Draw(contact)
for i,f in enumerate(files):
 im=Image.open(f).convert('RGB');im.thumbnail((210,165));x=i%6*cw;y=i//6*ch;contact.paste(im,(x,y+20));draw.text((x+5,y+3),'Map '+f.stem,fill='white')
contact.save(ROOT/'maps_contact_sheet.jpg',quality=90)
print('banks',len(index),'maps',len(files))
