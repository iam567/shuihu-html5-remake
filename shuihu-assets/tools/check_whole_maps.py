"""Grid check for whole-map redraws (prepare_whole_maps.py): did every object stay in its cells?

Works at the original 32 px scale. For each cell, a 64x64 window of the original centred on the cell is searched in the
downscaled redraw within +-RADIUS px (luminance + gradient correlation, as register_tiles.py). Only cells with
structure are judged. A cell is flagged when its content moved more than a quarter cell with a trusted match
(score >= MIN_SCORE); cells below MIN_SCORE are counted as uncertain (a style change alone lowers the score). The same
check on the tile-assembled maps-v2 picture, which is grid-locked by construction, is reported as the noise floor. Flags on cells next to a walkable/blocked boundary of the logic layer are the ones a player would
notice (standing in a wall, blocked by open ground). Writes production/<batch>/check/<job>.png (flags drawn in red,
boundary flags filled) and check.json.
Images already in check.json with an unchanged file are not checked again.
Usage: python3 tools/check_whole_maps.py BATCH
"""
import json,sys
from pathlib import Path
from PIL import Image,ImageDraw
import numpy as np
from register_tiles import features,match

ROOT=Path(__file__).resolve().parents[1];DIST=ROOT/'dist';RADIUS,MIN_SCORE,MIN_DETAIL,SHIFT=12,.3,4.0,8

def check(src,gen,logic,w,h,radius=RADIUS):
  gen=gen.resize(src.size,Image.Resampling.LANCZOS);fs,fg=features(src,1.0),features(gen,1.0)
  blocked=(np.array(logic).reshape(h,w)>=80);cells=[]
  for y in range(h):
    for x in range(w):
      x0,y0=min(max(x*32-16,0),w*32-64),min(max(y*32-16,0),h*32-64)
      t=[f[y0:y0+64,x0:x0+64] for f in fs]
      if t[1].mean()<MIN_DETAIL:continue
      dx,dy,score=match(fg,t,x0,y0,radius,64)
      edge=any(0<=y+j<h and 0<=x+i<w and blocked[y+j,x+i]!=blocked[y,x] for i,j in((1,0),(-1,0),(0,1),(0,-1)))
      cells.append({'x':x,'y':y,'dx':int(dx),'dy':int(dy),'score':round(score,3),'edge':edge,
        'flag':bool(max(abs(dx),abs(dy))>SHIFT and score>=MIN_SCORE),'uncertain':score<MIN_SCORE})
  return cells

if __name__=='__main__':
  batch=ROOT/'production'/sys.argv[1];out=batch/'check';out.mkdir(exist_ok=True)
  cat=json.loads((DIST/'data/catalog.json').read_text());orig={i['details']['mapId']:i for i in cat['items'] if i['category']=='maps' and not i.get('generated')}
  rules=json.loads((DIST/'data/tile-rules.json').read_text())['maps'];report=json.loads((batch/'check.json').read_text()) if (batch/'check.json').exists() else {}
  for job in json.loads((batch/'jobs.json').read_text()):
    p=batch/'aligned'/f"{job['id']}.png"   # align_whole_maps.py output when present
    if not p.exists():p=batch/f"{job['id']}.png"
    if not p.exists():print('missing',p.name);continue
    if report.get(job['id'],{}).get('mtime')==p.stat().st_mtime_ns:continue
    m=job['sourceId'];r=rules[m];src=Image.open(DIST/orig[m]['image']).convert('RGB');gen=Image.open(p).convert('RGB')
    cells=check(src,gen,r['logic'],r['width'],r['height']);flags=[c for c in cells if c['flag']]
    shifts=[max(abs(c['dx']),abs(c['dy'])) for c in cells]
    base=job['style'] if (DIST/f"generated/maps-v2/{job['style']}/{m}.webp").exists() else 'pixel-hd'
    floor=[c for c in check(src,Image.open(DIST/f"generated/maps-v2/{base}/{m}.webp").convert('RGB'),r['logic'],r['width'],r['height']) if c['flag']]
    report[job['id']]={'judged':len(cells),'flagged':len(flags),'boundaryFlagged':sum(c['edge'] for c in flags),
      'uncertain':sum(c['uncertain'] for c in cells),'tileVersionFlagged':len(floor),'tileVersionBoundaryFlagged':sum(c['edge'] for c in floor),
      'mtime':p.stat().st_mtime_ns,'aligned':p.parent.name=='aligned','medianShiftPx':float(np.median(shifts))*4 if shifts else 0,'medianScore':float(np.median([c['score'] for c in cells])) if cells else 0,'size':list(gen.size)}
    im=gen.resize(src.size,Image.Resampling.LANCZOS).resize((src.width*2,src.height*2));d=ImageDraw.Draw(im,'RGBA')
    for c in flags:d.rectangle((c['x']*64,c['y']*64,c['x']*64+63,c['y']*64+63),outline=(255,0,0,255),width=2,fill=(255,0,0,90) if c['edge'] else None)
    im.save(out/f"{job['id']}.png");print(job['id'],report[job['id']])
  (batch/'check.json').write_text(json.dumps(report,indent=1))
