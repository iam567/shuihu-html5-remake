from pathlib import Path
from PIL import Image
import json,hashlib
root=Path(__file__).resolve().parents[1];p=root/'dist/samples/jrpg-v1'
m=json.loads((root/'dist/data/tile-rules.json').read_text())['maps']['0106'];regions=json.loads((p/'regions.json').read_text())
im=Image.open(p/'components-generated.png').convert('RGB');assert im.size==(1536,1024)
old=Image.open(root/'dist/assets/map-0106.png').convert('RGB');tiles={};sources={}
for r in regions:
 x0,y0,x1,y1=r['source'];sx,sy,_,_=r['sheet']
 for y in range(y0,y1,32):
  for x in range(x0,x1,32):
   tile=m['graphics'][y//32*10+x//32]
   if tile in tiles:continue
   cx=sx+(x-x0)*4;cy=sy+(y-y0)*4
   tiles[tile]=im.crop((cx,cy,cx+128,cy+128));sources[tile]=r['name']
(p/'tiles').mkdir(exist_ok=True)
for tile,img in tiles.items():img.save(p/'tiles'/f'{tile:03d}.png')
new=Image.new('RGB',(1280,1280));count=0
for i,tile in enumerate(m['graphics']):
 x=i%10;y=i//10
 piece=tiles.get(tile)
 if piece is None:piece=old.crop((x*32,y*32,x*32+32,y*32+32)).resize((128,128),Image.Resampling.NEAREST)
 else:count+=1
 new.paste(piece,(x*128,y*128))
new.save(p/'room-assembled.png')
comparison=Image.new('RGB',(2560,1280));comparison.paste(Image.open(p/'original.png'),(0,0));comparison.paste(new,(1280,0));comparison.save(p/'comparison.png')
manifest=dict(mapId='0106',model='gpt-image-2.5-sunburst',method='Six source patches redrawn, split into 128px tiles, deduplicated by original graphic ID, assembled using original 10x10 map indices. Remaining tiles nearest-neighbor enlarged originals.',redrawnUniqueTiles=len(tiles),replacedCells=count,totalCells=100,tiles=sources,graphics=m['graphics'],logic=m['logic'],limitations=['Partial style sample, includes original tiles','AI geometry and seams require manual QA before game integration','Exploration logic preserved as data; no runtime gameplay test','Battle water access not established'])
(p/'manifest.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2));print(json.dumps({k:manifest[k] for k in ['redrawnUniqueTiles','replacedCells','totalCells']}))
