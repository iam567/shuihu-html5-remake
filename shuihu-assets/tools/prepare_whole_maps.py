"""Whole-map redraw jobs: the generator repaints an entire original map in one picture instead of tile by tile.

The reference is the original map at nearest-neighbour scale, 128 px per 32 px cell when the model's size limits allow
it and otherwise the largest multiple of 16 that fits (gpt-image-2: edges multiple of 16, at most 3840 px, at most
8,294,400 px), so the output is used at native size; jobs record that cell size. Gameplay never reads the picture: passability and events live in each map's logic layer, which
stays as in the ROM, so the prompt insists on every object keeping its exact cells.
Writes production/<batch>/{<map>-reference.png, <job>.txt, jobs.json}; with --max N the jobs are split over
<batch>-1, <batch>-2 … of at most N jobs, both styles of a map staying together. Nothing is submitted.
Usage: python3 tools/prepare_whole_maps.py BATCH STYLE[,STYLE...] [--max N] [--skip JOBID,...] MAPID ...|all
"""
import json,sys
from pathlib import Path
from PIL import Image

ROOT=Path(__file__).resolve().parents[1];DIST=ROOT/'dist';CELL,MAX_EDGE,MAX_PIXELS=128,3840,8294400

def cell_size(w,h):
  c=CELL
  while c>16 and (max(w,h)*c>MAX_EDGE or w*h*c*c>MAX_PIXELS):c-=16
  return c
STYLES={'pixel-hd':'modern crisp high-resolution JRPG pixel art, clean readable clustered shading',
        'unreal':'stylized realistic PBR game environment with neutral daylight, like a modern 3D strategy game rendered top-down',
        'ghibli':'warm hand-painted animation background art, Ghibli inspired, soft watercolour-like brushwork',
        'gongbi':'traditional Chinese gongbi painting with fine ink outlines and mineral blue-green colours on silk, Song dynasty landscape feel',
        'hd2d':'HD-2D style: detailed pixel-art textures lit like a 3D diorama, soft ambient occlusion, gentle bloom and warm sunlight'}

def prompt(desc):
  return (f'Use case: style-transfer. Edit target: the supplied top-down map of an old 16-bit Chinese strategy RPG (Water Margin, Song '
    f'dynasty). Repaint the whole map as one coherent high-resolution picture in {desc}. The output must line up pixel for pixel with '
    'the reference when overlaid: same scale, no zoom, no crop, no shift. The map is a grid of square cells; every house, wall, gate, '
    'door, tree, rock, cliff, fence, river bank, road, floor area and piece of furniture (tables, stools, screens, vases, cabinets, '
    'counters) must stay in exactly the same cells with the same footprint, outline and orientation, and the same number of each, '
    'because the game logic for walking is fixed per cell. Pure black areas of the reference are empty space outside the map: keep '
    'them pure black #000000 with exactly the same shape, and never extend rooms, walls, floors or ground into them. Keep the same '
    'three-quarter top-down camera, the same doors and windows, and the same materials and colour scheme as the reference. Draw objects '
    'whole and continuous: a building is one building, a tree is one tree, walls run straight, roads and grass flow naturally with no '
    'visible tiling, seams or repeated patches. Do not add or remove objects, do not move anything, do not add characters, animals, '
    'text, letters, signboard writing, UI, grid lines, borders, frames or vignettes.')

if __name__=='__main__':
  args=sys.argv[1:];opt=lambda k,d:args[args.index(k)+1] if k in args else d
  limit=int(opt('--max',0));skip=set(filter(None,opt('--skip','').split(',')))
  for k in ('--max','--skip'):
    if k in args:i=args.index(k);del args[i:i+2]
  batch,styles,maps=args[0],args[1].split(','),args[2:]
  cat=json.loads((DIST/'data/catalog.json').read_text());orig={i['details']['mapId']:i for i in cat['items'] if i['category']=='maps' and not i.get('generated')}
  rules=json.loads((DIST/'data/tile-rules.json').read_text())['maps']
  if maps==['all']:maps=sorted(orig)
  groups=[[(m,s) for s in styles if f'{m}-{s}' not in skip] for m in maps];groups=[g for g in groups if g]
  batches=[[]]
  for g in groups:
    if limit and len(batches[-1])+len(g)>limit:batches.append([])
    batches[-1].extend(g)
  summary=[]
  for n,items in enumerate(batches,1):
    name=f'{batch}-{n}' if limit else batch;out=ROOT/'production'/name;out.mkdir(parents=True,exist_ok=True);jobs=[]
    for m,s in items:
      c=cell_size(rules[m]['width'],rules[m]['height']);w,h=rules[m]['width']*c,rules[m]['height']*c
      assert w%16==0 and h%16==0 and max(w,h)<=MAX_EDGE and w*h<=MAX_PIXELS and max(w,h)/min(w,h)<=3,f'{m} is {w}x{h}'
      if not (out/f'{m}-reference.png').exists():Image.open(DIST/orig[m]['image']).convert('RGB').resize((w,h),Image.Resampling.NEAREST).save(out/f'{m}-reference.png')
      (out/f'{m}-{s}.txt').write_text(prompt(STYLES[s]))
      jobs.append({'id':f'{m}-{s}','kind':'whole-map','style':s,'reference':f'{m}-reference.png','size':f'{w}x{h}','cell':c,'sourceId':m})
    (out/'jobs.json').write_text(json.dumps(jobs,indent=2));summary.append({'batch':name,'jobs':len(jobs)})
  print(json.dumps(summary))
