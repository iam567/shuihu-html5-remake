"""Normalise generated HD walk sheets (3x3 figures on magenta) into the game's runtime sheets.

Rows are front / back / left profile, columns idle / left step / right step (original frames 0-8 in reading order).
Each third of the generated image is keyed (soft magenta alpha, as slice_ui_buttons.py), its figure's opaque bounds are
found, and all nine figures are re-placed with ONE scale per sheet (so the walk cycle does not pulse) on a common
baseline. Horizontally the standing frame of each row is centred and the two step frames are shifted so that their upper
body (head and torso: column profile of the top UPPER of the figure) best matches the standing frame, so legs and arm
swing do not drag the body sideways. If one step frame's upper body clearly differs from the standing frame (IoU of the
aligned upper-body masks below MIN_IOU, e.g. a weapon that appears in only that frame) while the other step matches, the
matching step is used for both, so nothing pops in and out during the walk. Writes shuihu-html5/dist/assets/characters-hd/<bank>.webp (3x3 cells of
CELL px) and merges entries into shuihu-html5/dist/data/characters-hd.json (scale = map tiles per cell pixel).
Usage: python3 tools/export_hd_sprites.py BATCH [BANK ...]
"""
import json,sys
from pathlib import Path
import numpy as np
from PIL import Image
from slice_ui_buttons import key

ROOT=Path(__file__).resolve().parents[1];GAME=ROOT.parent/'shuihu-html5/dist'
CELL,FILL,FOOT,TILES=160,0.9,6,1.35   # cell px, tallest figure fills 90% of a cell, feet 6 px above its bottom, cell = 1.35 tiles
UPPER=0.55   # share of the figure height used to register step frames to the standing frame
MIN_IOU=0.82  # upper-body mask agreement below which a step frame is replaced by the row's other step
# Reviewed by eye where the automatic check cannot tell (bank -> {row: step to use for both steps}).
STEP_OVERRIDES={'100400':{2:1}}   # hero, profile: the right step shows the back sword's hilt; use the left step twice

def figures(rgba):
  H,W=rgba.shape[:2];out=[]
  for r in range(3):
    for c in range(3):
      y0,y1,x0,x1=r*H//3,(r+1)*H//3,c*W//3,(c+1)*W//3;a=rgba[y0:y1,x0:x1];m=a[...,3]>40
      ys,xs=np.nonzero(m)
      if not len(ys):raise ValueError(f'empty cell {r},{c}')
      out.append(a[ys.min():ys.max()+1,xs.min():xs.max()+1])
  return out

if __name__=='__main__':
  batch=ROOT/'production'/sys.argv[1];only=set(sys.argv[2:]);manifest_path=GAME/'data/characters-hd.json'
  manifest=json.loads(manifest_path.read_text()) if manifest_path.exists() else {'sheets':{}}
  manifest['note']=('HD walk sheets: 3x3 cells front/back/left x idle/step-left/step-right, right = mirrored left. Original frames 0-8 '
                    'map to cells in reading order; feet on a common baseline; scale is map tiles per cell pixel.')
  (GAME/'assets/characters-hd').mkdir(parents=True,exist_ok=True);swapped=[]
  for job in json.loads((batch/'jobs.json').read_text()):
    bank=job['sourceId'];png=batch/f"{job['id']}.png"
    if (only and bank not in only) or not png.exists():continue
    figs=figures(key(Image.open(png)));scale=CELL*FILL/max(f.shape[0] for f in figs)
    sheet=Image.new('RGBA',(CELL*3,CELL*3),(0,0,0,0))
    ims=[Image.fromarray(f.astype(np.uint8)) for f in figs]
    ims=[im.resize((max(1,round(im.width*scale)),max(1,round(im.height*scale))),Image.Resampling.LANCZOS) for im in ims]
    def profile(im):
      a=np.asarray(im)[...,3].astype(float);return a[:max(1,int(a.shape[0]*UPPER))].sum(axis=0)
    for row in range(3):
      placed={};idle=ims[row*3];ref=profile(idle);x_idle=(CELL-idle.width)//2
      for col in range(3):
        im=ims[row*3+col]
        if col==0:x=x_idle
        else:
          prof=profile(im);best=None
          for x in range(-im.width+8,CELL-8):
            lo,hi=max(x,x_idle),min(x+im.width,x_idle+idle.width)
            if hi<=lo:continue
            score=float((prof[lo-x:hi-x]*ref[lo-x_idle:hi-x_idle]).sum())
            if best is None or score>best[0]:best=(score,x)
          x=best[1]
        placed[col]=(im,min(max(x,0),CELL-im.width))
      # Upper-body agreement of each step with the standing frame, on the cell canvas.
      cut=CELL-FOOT-int(placed[0][0].height*(1-UPPER))   # same line for all three, from the standing frame
      def upper(col):
        im,x=placed[col];m=np.zeros((CELL,CELL),bool);a=np.asarray(im)[...,3]>40;y=CELL-FOOT-im.height;m[y:y+im.height,x:x+im.width]=a
        return m[:cut]
      iou=[1.0]+[float((upper(c)&upper(0)).sum()/max(1,(upper(c)|upper(0)).sum())) for c in (1,2)]
      if row in STEP_OVERRIDES.get(bank,{}):keep=STEP_OVERRIDES[bank][row];placed[1]=placed[2]=placed[keep];swapped.append(f'{bank} row{row} both=step{keep} (override)')
      elif iou[1]<MIN_IOU<=iou[2]:placed[1]=placed[2];swapped.append(f'{bank} row{row} step1')
      elif iou[2]<MIN_IOU<=iou[1]:placed[2]=placed[1];swapped.append(f'{bank} row{row} step2')
      for col,(im,x) in placed.items():sheet.alpha_composite(im,(col*CELL+x,row*CELL+CELL-FOOT-im.height))
    rel=f'assets/characters-hd/{bank}.webp';sheet.save(GAME/rel,'WEBP',quality=90,method=6)
    manifest['sheets'][bank]={'image':rel,'cell':CELL,'scale':TILES/CELL,'source':f'{batch.name}/{png.name}','style':'hd-painted'}
    print(bank,'scale',round(scale,3))
  # Sheets not redrawn in this style are dropped so they fall back to the original pixel sprites (no mixed styles).
  manifest['sheets']={b:v for b,v in manifest['sheets'].items() if v.get('style')=='hd-painted'}
  manifest_path.write_text(json.dumps(manifest,ensure_ascii=False,indent=1));print(len(manifest['sheets']),'HD sheets in the game')
  print('step frames replaced:',len(swapped),swapped)
