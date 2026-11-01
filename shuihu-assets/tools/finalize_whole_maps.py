"""Turn whole-map redraws (prepare_whole_maps.py) into game art and the game's style manifest.

For every generated <map>-<style>.png in the given batches: the shop signs of data/map-signs.json (drawn at 128 px per
cell, from the workshop's sign layers) are painted back at their original cells, scaled to the job's cell size, since
the generator is told not to draw writing; the result is saved as shuihu-html5/dist/assets/maps-hd/<style>/<map>.webp.
check_whole_maps.py results choose, per map and style, the redraw with the fewest boundary flags (objects moved next to
a walkable/blocked edge) across all given batches; it is marked geometryVerified when it has no more than the
tile-assembled version (+SLACK, now 0). Unverified maps are listed for another whole-map redraw.
Writes shuihu-html5/dist/data/art-styles.json (keeps "previews"; replaces "styles").
Usage: python3 tools/finalize_whole_maps.py BATCH ...
"""
import json,sys
from pathlib import Path
from PIL import Image,ImageDraw,ImageFont

ROOT=Path(__file__).resolve().parents[1];DIST=ROOT/'dist';GAME=ROOT.parent/'shuihu-html5/dist';SLACK,QUALITY=0,82;GAME_STYLES={'ghibli','hd2d'}   # styles offered in the game's settings
FONT='/System/Library/Fonts/STHeiti Medium.ttc'

def colour(v):return None if not v or v=='none' else v

SIGN_ART=ROOT/'dist/generated/signs'   # painted signboards (production/signs-1), one PNG per label; text is the fallback
def paint_signs(im,signs,k):
  d=ImageDraw.Draw(im)
  for s in signs:
    art=SIGN_ART/f"{s['label']}.png"
    if art.exists():
      # Painted plaque over the sign's outer box, a little larger so it reads as a hanging board.
      r=s['rects'][0];x,y,w,h=(float(r[a])*k for a in ('x','y','width','height'));board=Image.open(art).convert('RGBA')
      bw=w*1.12;bh=bw*board.height/board.width;board=board.resize((max(1,round(bw)),max(1,round(bh))),Image.Resampling.LANCZOS)
      base=im.convert('RGBA');base.alpha_composite(board,(round(x+w/2-bw/2),round(y+h/2-bh/2)));im.paste(base.convert(im.mode));continue
    for r in s['rects']:
      x,y,w,h=(float(r[a])*k for a in ('x','y','width','height'))
      d.rectangle((x,y,x+w-1,y+h-1),fill=colour(r.get('fill')),outline=colour(r.get('stroke')),width=max(1,round(float(r.get('stroke-width',0))*k)) if r.get('stroke') else 0)
    t=s['text'];font=ImageFont.truetype(FONT,max(8,round(float(t['font-size'])*k)));gap=float(t.get('letter-spacing',0))*k
    chars=t['value'];widths=[d.textlength(c,font=font) for c in chars];total=sum(widths)+gap*(len(chars)-1)
    x=float(t['x'])*k-total/2;y=float(t['y'])*k
    for c,w in zip(chars,widths):d.text((x,y),c,font=font,fill=t.get('fill','#000'),anchor='lm');x+=w+gap
  return im

if __name__=='__main__':
  assets=json.loads((GAME/'data/assets.json').read_text());maps={m['id']:m for m in assets['maps']}
  signs=json.loads((DIST/'data/map-signs.json').read_text())['maps'];path=GAME/'data/art-styles.json'
  manifest=json.loads(path.read_text()) if path.exists() else {'version':1}
  # Every checked redraw of a map in a style is a candidate; the one with the fewest boundary flags over the
  # tile-assembled version wins (later batch on ties).
  best={}
  for order,batch in enumerate(map(lambda b:ROOT/'production'/b,sys.argv[1:])):
    check=json.loads((batch/'check.json').read_text()) if (batch/'check.json').exists() else {}
    for job in json.loads((batch/'jobs.json').read_text()):
      png=batch/'aligned'/f"{job['id']}.png"
      if not png.exists():png=batch/f"{job['id']}.png"
      c=check.get(job['id'])
      if job['style'] not in GAME_STYLES or not png.exists() or job['sourceId'] not in maps or not c:continue
      key=(job['style'],job['sourceId']);score=(c['boundaryFlagged']-c['tileVersionBoundaryFlagged'],c['flagged'],-order)
      if key not in best or score<best[key][0]:best[key]=(score,png,job,c,batch.name)
  styles={s:{'maps':{}} for s in GAME_STYLES}
  for style in GAME_STYLES:
    for mid,m in maps.items():
      rel=f"assets/maps-hd/{style}/{mid}.webp";(GAME/rel).parent.mkdir(parents=True,exist_ok=True);cand=best.get((style,mid))
      if cand:
        _,png,job,c,bname=cand;im=Image.open(png).convert('RGB');cell=job.get('cell') or im.width//m['widthTiles']
        assert (im.width,im.height)==(m['widthTiles']*cell,m['heightTiles']*cell),(job['id'],im.size)
        if mid in signs:paint_signs(im,signs[mid]['signs'],cell/signs[mid]['cell'])
        im.save(GAME/rel,'WEBP',quality=QUALITY,method=6)
        styles[style]['maps'][mid]={'status':'approved','source':'whole-map','geometryVerified':cand[0][0]<=SLACK,'signsVerified':True,'width':m['widthPixels'],'height':m['heightPixels'],
          'image':rel,'scale':cell/32,'check':{k:c[k] for k in ('flagged','boundaryFlagged','tileVersionBoundaryFlagged','uncertain')},'batch':bname}
        continue
  manifest.update(version=3,policy=('Per map and style the whole-map redraw with the fewest boundary flags (tools/check_whole_maps.py) is used; '
    'geometryVerified tells whether it has no more than the tile-assembled version (+SLACK). Tile-assembled pictures are never used.'),styles=styles)
  path.write_text(json.dumps(manifest,ensure_ascii=False,indent=1))
  print(json.dumps({s:{'maps':len(v['maps']),'verified':sum(x['geometryVerified'] for x in v['maps'].values())} for s,v in styles.items()}))
  for s,v in styles.items():print(s,'to redraw:',' '.join(sorted(k for k,x in v['maps'].items() if not x['geometryVerified'])))
