import json,math
from pathlib import Path
from PIL import Image
root=Path(__file__).resolve().parents[1];dist=root/'dist';out=root/'production/batch-005';out.mkdir(exist_ok=True)
c=json.loads((dist/'data/catalog.json').read_text());jobs=[]
styles={'pixel-hd':'modern crisp JRPG pixel art, clean readable clustered shading','unreal':'stylized realistic PBR game textures with neutral flat lighting','ghibli':'warm hand-painted animation background art, Ghibli inspired'}
for bank in ['bank-053fd4-07cbea-0dde08','bank-04b710-07a56a-0dde48']:
 item=next(i for i in c['items'] if i['id']==bank);src=Image.open(dist/item['image']).convert('RGB');count=src.width//32*(src.height//32);rows=math.ceil(count/8);ref=Image.new('RGB',(1280,rows*160),(255,0,255))
 for n in range(count):
  tile=src.crop((n%16*32,n//16*32,n%16*32+32,n//16*32+32)).resize((128,128),Image.Resampling.NEAREST);ref.paste(tile,(n%8*160+16,n//8*160+16))
 name=bank+'-gutter-reference.png';ref.save(out/name)
 for style,desc in styles.items():
  id=bank+'-'+style+'-repair';prompt=f'''Use case: style-transfer. Edit target: supplied modular game tile atlas with deliberate magenta gutters. Redraw every individual 128x128 tile inside its own cell, in {desc}. EXACTLY 8 columns and {rows} rows. Preserve reading order, all tile identities and indices, object orientation, topology, boundaries and source color themes. Preserve all magenta separator gutters as flat pure #ff00ff. Every occupied tile is a complete square of artwork, centered in its cell, with the same canvas dimensions and tile positions as reference. Do not add black or colored borders, outlines, drop shadows, vignette, beveled edges, seams or padding INSIDE the square tile. Flat terrain tiles must fill their entire square edge to edge and tile seamlessly when repeated; matching edges between grass, water, rock and stairs must connect without stripes. Never turn magenta gutters into scenery. Empty BLACK source tiles stay black squares. Do not combine tiles into a scene. Preserve partial objects as the same partial fragments; do not invent complete objects inside every cell. No text or grid labels. This is a production repair: black vertical lines and bright colored edge contamination are unacceptable.'''
  (out/(id+'.txt')).write_text(prompt);jobs.append(dict(id=id,kind='map-bank-repair',style=style,reference=name,size='auto',sourceId=bank,columns=8,rows=rows,cellSize=160,innerSize=128,gutter=16))
(out/'jobs.json').write_text(json.dumps(jobs,indent=2));print(len(jobs),'repaired atlas jobs')
