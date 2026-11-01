"""Before/after sheets for regenerated style maps: committed maps-v2 (git HEAD) next to the working copy.
Usage: python3 tools/compare_map_repairs.py OUTDIR MAPID[:x,y,w,h] ...   (crop in map pixels, default whole map)"""
import io,subprocess,sys
from pathlib import Path
from PIL import Image,ImageDraw
root=Path(__file__).resolve().parents[2];out=Path(sys.argv[1]);out.mkdir(parents=True,exist_ok=True)
for arg in sys.argv[2:]:
  mid,_,crop=arg.partition(':');rows=[]
  for style in ['pixel-hd','unreal','ghibli']:
    rel=f'shuihu-assets/dist/generated/maps-v2/{style}/{mid}.webp'
    old=Image.open(io.BytesIO(subprocess.run(['git','-C',str(root),'show',f'HEAD:{rel}'],capture_output=True,check=True).stdout)).convert('RGB')
    new=Image.open(root/rel).convert('RGB')
    box=tuple(int(v) for v in crop.split(',')) if crop else (0,0,new.width,new.height);box=(box[0],box[1],box[0]+box[2],box[1]+box[3]) if crop else box
    a,b=old.crop(box),new.crop(box);scale=min(1,900/a.width);a,b=[i.resize((round(i.width*scale),round(i.height*scale))) for i in (a,b)]
    row=Image.new('RGB',(a.width*2+30,a.height+28),'#f1eee4');row.paste(a,(0,28));row.paste(b,(a.width+30,28))
    d=ImageDraw.Draw(row);d.text((6,6),f'{mid} {style} before',fill='#222');d.text((a.width+36,6),'after',fill='#222');rows.append(row)
  sheet=Image.new('RGB',(rows[0].width,sum(r.height for r in rows)),'white');y=0
  for r in rows:sheet.paste(r,(0,y));y+=r.height
  sheet.save(out/f'compare-{mid}{"-crop" if crop else ""}.jpg',quality=88);print('wrote',out/f'compare-{mid}.jpg')
