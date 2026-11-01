"""Find multi-tile objects (trees, buildings, bridges...) that must be redrawn as one picture.

Generated atlases redraw every 32x32 cell on its own. Where an object's cells sit apart in the source atlas (a 2x2
tree whose quarters are scattered between wells and roofs), each quarter comes back as an unrelated picture and no
cutting can make them meet. An object here is a connected set of non-ground map cells whose original pixels run on
across each shared edge. Identical layouts on several maps count once. Writes data/object-groups.json.
Usage: python3 tools/find_object_groups.py
"""
import json,hashlib
from collections import Counter
from pathlib import Path
import numpy as np
from PIL import Image
from tile_seams import adjacency,_continuous

ROOT=Path(__file__).resolve().parents[1]/'dist'
rules=json.loads((ROOT/'data/tile-rules.json').read_text());catalog=json.loads((ROOT/'data/catalog.json').read_text())
banks={i['id']:i for i in catalog['items'] if i['category']=='map-banks'}
groups={}
for bank_id,bank in banks.items():
  src=np.asarray(Image.open(ROOT/bank['image']).convert('RGB'));cols=src.shape[1]//32
  tile=lambda t:src[t//cols*32:t//cols*32+32,t%cols*32:t%cols*32+32]
  counts=adjacency(rules,bank_id);ground={t for (a,t,b),n in counts.items() if a=='x' and t==b and counts[('y',t,t)]}
  blank={t for t in range(cols*(src.shape[0]//32)) if tile(t).max()<12}
  cont={}
  def joined(a,b,axis):
    if (a,b,axis) not in cont:cont[(a,b,axis)]=_continuous({a:tile(a),b:tile(b)},a,b,axis)
    return cont[(a,b,axis)]
  for map_id,m in rules['maps'].items():
    if m['bankId']!=bank_id:continue
    g=np.array(m['graphics']).reshape(m['height'],m['width']);H,W=g.shape;seen=np.zeros_like(g,bool)
    for y in range(H):
      for x in range(W):
        if seen[y,x] or g[y,x] in ground or g[y,x] in blank:continue
        stack,cells=[(y,x)],[];seen[y,x]=True
        while stack:
          cy,cx=stack.pop();cells.append((cy,cx))
          for dy,dx,axis in ((0,1,'x'),(1,0,'y'),(0,-1,'x'),(-1,0,'y')):
            ny,nx=cy+dy,cx+dx
            if not(0<=ny<H and 0<=nx<W) or seen[ny,nx]:continue
            t=g[ny,nx]
            if t in ground or t in blank:continue
            a,b=(g[cy,cx],t) if dy+dx>0 else (t,g[cy,cx])
            if joined(int(a),int(b),axis):seen[ny,nx]=True;stack.append((ny,nx))
        if len(cells)<2:continue
        ys=[c[0] for c in cells];xs=[c[1] for c in cells];y0,x0=min(ys),min(xs)
        layout=[[-1]*(max(xs)-x0+1) for _ in range(max(ys)-y0+1)]
        for cy,cx in cells:layout[cy-y0][cx-x0]=int(g[cy,cx])
        key=hashlib.sha1(json.dumps([bank_id,layout]).encode()).hexdigest()[:12]
        entry=groups.setdefault(key,{'id':key,'bankId':bank_id,'layout':layout,'maps':[]})
        entry['maps'].append({'mapId':map_id,'x':x0,'y':y0})
for e in groups.values():
  cols=banks[e['bankId']]['width']//32;L=e['layout'];split=0
  for y,row in enumerate(L):
    for x,t in enumerate(row):
      for nx,ny in ((x+1,y),(x,y+1)):
        if t<0 or ny>=len(L) or nx>=len(row) or L[ny][nx]<0:continue
        u=L[ny][nx];split+=not((nx==x+1 and u==t+1 and t%cols<cols-1) or (ny==y+1 and u==t+cols))
  e['tiles']=sorted({t for r in L for t in r if t>=0});e['cells']=sum(t>=0 for r in L for t in r);e['scatteredSeams']=split;e['uses']=len(e['maps'])
out=sorted(groups.values(),key=lambda e:(e['bankId'],-e['cells'],e['id']))
(ROOT/'data/object-groups.json').write_text(json.dumps({'description':'Multi-tile objects found by tools/find_object_groups.py','count':len(out),'groups':out}))
need=[e for e in out if e['scatteredSeams']]
sizes=Counter(min(e['cells'],40)//5*5 for e in need)
print(json.dumps({'groups':len(out),'withScatteredSeams':len(need),'cells':sum(e['cells'] for e in need),'largest':max((e['cells'] for e in need),default=0),
  'banksAffected':len({e['bankId'] for e in need}),'sizeBuckets':dict(sorted(sizes.items())),'distinctTilesInvolved':len({(e['bankId'],t) for e in need for t in e['tiles']})}))
