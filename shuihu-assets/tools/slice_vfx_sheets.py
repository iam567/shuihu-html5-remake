"""Cut generated hit-effect sheets (5 animations x 6 frames on magenta) into the game's effect atlases.

The sheet is keyed like the UI buttons (slice_ui_buttons.key, soft magenta alpha). The prompt asks for a strict grid, so
rows and columns are the equal fifths / sixths of the image; bounds use solid pixels only and ignore an EDGE px border
(the generator sometimes leaves off-magenta corners). Every frame of a row is
re-centred on the row's common centre (centre of the union of its frames' bounds, so a projectile still travels) and
scaled with ONE factor per row so the largest frame fills FILL of a cell. Writes
shuihu-html5/dist/assets/vfx/<name>.webp: 6 x 5 cells of CELL px, row = animation, column = frame.
Usage: python3 tools/slice_vfx_sheets.py SHEET.png NAME
"""
import sys
from pathlib import Path
import numpy as np
from PIL import Image
from slice_ui_buttons import key

ROOT=Path(__file__).resolve().parents[1];GAME=ROOT.parent/'shuihu-html5/dist'
CELL,FILL,ROWS,COLS,EDGE=128,0.92,5,6,24

if __name__=='__main__':
  sheet,name=Path(sys.argv[1]),sys.argv[2];rgba=key(Image.open(sheet));a=rgba[...,3]>120;H,W=a.shape;a[:EDGE]=a[-EDGE:]=False;a[:,:EDGE]=a[:,-EDGE:]=False
  out=Image.new('RGBA',(CELL*COLS,CELL*ROWS),(0,0,0,0))
  for r,(y0,y1) in enumerate((r*H//ROWS,(r+1)*H//ROWS) for r in range(ROWS)):
    frames=[]
    for c in range(COLS):
      x0,x1=c*W//COLS,(c+1)*W//COLS;m=a[y0:y1,x0:x1];ys,xs=np.nonzero(m)
      frames.append(None if not len(ys) else (x0+xs.min(),y0+ys.min(),x0+xs.max()+1,y0+ys.max()+1))
    boxes=[f for f in frames if f];ux0=min(b[0] for b in boxes);uy0=min(b[1] for b in boxes);ux1=max(b[2] for b in boxes);uy1=max(b[3] for b in boxes)
    span=max(max(b[2]-b[0],b[3]-b[1]) for b in boxes);scale=CELL*FILL/span
    cx,cy=(ux0+ux1)/2,(uy0+uy1)/2
    for c,f in enumerate(frames):
      if not f:continue
      # Keep each frame's offset from the row centre, clamped so it stays inside its cell.
      im=Image.fromarray(rgba[f[1]:f[3],f[0]:f[2]].astype(np.uint8));im=im.resize((max(1,round(im.width*scale)),max(1,round(im.height*scale))),Image.Resampling.LANCZOS)
      fx=((f[0]+f[2])/2-(c*W//COLS+(c+1)*W//COLS)/2-(cx-(ux0+ux1)/2))*scale;fy=((f[1]+f[3])/2-cy)*scale
      px=round(c*CELL+CELL/2+fx-im.width/2);py=round(r*CELL+CELL/2+fy-im.height/2)
      px=min(max(px,c*CELL),c*CELL+CELL-im.width);py=min(max(py,r*CELL),r*CELL+CELL-im.height)
      out.alpha_composite(im,(px,py))
  (GAME/'assets/vfx').mkdir(parents=True,exist_ok=True);out.save(GAME/f'assets/vfx/{name}.webp','WEBP',quality=88,method=6);print(name,out.size)
