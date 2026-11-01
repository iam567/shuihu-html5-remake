from extract_graphics import *
from PIL import ImageDraw
out=ROOT/'text';out.mkdir(exist_ok=True);rawout=out/'raw';rawout.mkdir(exist_ok=True);pngout=out/'dialogue_pages';pngout.mkdir(exist_ok=True)
def tokens_for(raw,portrait=False):
 tokens=[];bank=0;i=0;need_portrait=portrait
 while i<len(raw):
  x=raw[i];pos=i;i+=1
  if need_portrait and x<0xf0:tokens.append({'offset':pos,'type':'portrait','id':x});need_portrait=False;continue
  need_portrait=False
  if x<0xf0:tokens.append({'offset':pos,'type':'glyph','bank':bank,'code':x})
  elif x<0xfc:bank=x-0xf0;tokens.append({'offset':pos,'type':'font_bank','bank':bank})
  elif x==0xfc:tokens.append({'offset':pos,'type':'color_toggle'})
  elif x==0xfd:
   arg=raw[i] if i<len(raw) else None;i+=1;tokens.append({'offset':pos,'type':'speed','value':arg})
  elif x==0xfe:tokens.append({'offset':pos,'type':'newline'})
  else:
   flag=raw[i] if i<len(raw) else None;i+=1;tokens.append({'offset':pos,'type':'segment_end','continuation_byte':flag});need_portrait=portrait
 return tokens
def render(ts,label,path):
 x=0;y=22;placements=[];labels=[]
 for t in ts:
  typ=t['type']
  if typ=='portrait':labels.append((y,'Portrait '+str(t['id'])));y+=16;x=0
  elif typ=='glyph':
   f=ROOT/'fonts'/f"bank{t['bank']}_{t['code']:02x}.png"
   if f.exists():placements.append((x,y,f))
   x+=16
   if x>=256:x=0;y+=16
  elif typ in ('newline','segment_end'):
   x=0;y+=20
 im=Image.new('RGB',(288,y+24),'white');d=ImageDraw.Draw(im);d.text((4,3),label,fill='black')
 for yy,l in labels:d.text((8,yy),l,fill=(80,80,80))
 for xx,yy,f in placements:
  g=Image.open(f);im.paste(g,(16+xx,yy),g)
 im.save(path)
ptrs=list(struct.unpack('>510I',rom[0xbc6e4:0xbcedc]));rows=[]
for i,a in enumerate(ptrs):
 end=ptrs[i+1] if i+1<len(ptrs) else a+rom[a:].find(b'\xff\x00')+2
 raw=rom[a:end];tokens=tokens_for(raw,True);(rawout/f'dialogue_{i:03d}.bin').write_bytes(raw);render(tokens,f'Dialogue {i:03d} / ROM {a:06X}',pngout/f'{i:03d}.png')
 rows.append({'id':i,'start':hex(a),'end':hex(end),'raw_hex':raw.hex(),'tokens':tokens,'parse_status':'static interpretation; continuation behavior not fully runtime verified','end_status':'next pointer boundary' if i<509 else 'inferred from first FF00'})
(out/'dialogues.json').write_text(json.dumps(rows,ensure_ascii=False,indent=2))
for name,base,count,fixed in [('item_skill_names',0xad17c,143,0),('character_names',0xad690,52,0),('job_names',0xad5fa,30,5)]:
 records=[];contact=Image.new('RGB',(320,24*count+24),'white');draw=ImageDraw.Draw(contact)
 for i in range(count):
  a=base+i*fixed if fixed else base+struct.unpack_from('>h',rom,base+i*2)[0];end=a+fixed if fixed else rom.index(b'\xff',a)+1;raw=rom[a:end];ts=tokens_for(raw);records.append({'id':i,'rom':hex(a),'raw_hex':raw.hex(),'tokens':ts});draw.text((4,i*24+3),f'{i:03d}',fill='black');x=44
  for t in ts:
   if t['type']=='glyph':
    f=ROOT/'fonts'/f"bank{t['bank']}_{t['code']:02x}.png"
    if f.exists():g=Image.open(f);contact.paste(g,(x,i*24),g)
    x+=16
 contact.save(out/(name+'.png'));(out/(name+'.json')).write_text(json.dumps(records,ensure_ascii=False,indent=2))
print('dialogues',len(rows))
