from extract_graphics import *
from collections import Counter
mapsroot=ROOT.parent/'logic/maps'
records=json.loads((mapsroot/'maps.json').read_text()); spawns=json.loads((mapsroot/'spawn_records.json').read_text())
candidates=json.loads((mapsroot/'map_dimensions_candidates.json').read_text())
out=ROOT/'maps';out.mkdir(exist_ok=True); idx=[]
for r in records:
 layer=(mapsroot/r['layers'][1]['file']).read_bytes()
 if not layer:continue
 dims=Counter((s['layer1_width'],s['layer1_height']) for s in spawns if s['id'][:2]==r['id'][:2] and s['layer1_width']*s['layer1_height']==len(layer))
 scriptdims=Counter((s['width'],s['height']) for s in candidates if s['map_id']==r['id'] and s['width']*s['height']==len(layer))
 status='inferred_from_script_pattern_and_matching_area' if scriptdims else 'inferred_from_same_group_matching_area'
 if scriptdims:dims=scriptdims
 if r['id'] in {'0408':(24,15),'0a06':(24,25)}:
  dims=Counter([{'0408':(24,15),'0a06':(24,25)}[r['id']]]);status='explicit_battle_opcode_0025_dimensions'
 if not dims:continue
 w,h=dims.most_common(1)[0][0];data,end=tiles(r['tiles']);data=bytes(0x200*32)+data;pal=palette(r['palette']);meta={}
 for v in set(layer):
  words=struct.unpack('>16H',rom[r['metatiles']+v*32:r['metatiles']+v*32+32]); im=Image.new('RGBA',(32,32))
  for j,t in enumerate(words):im.paste(tile_image(data,t&2047,pal,t),(j%4*8,j//4*8))
  meta[v]=im
 im=Image.new('RGBA',(w*32,h*32))
 for j,v in enumerate(layer):im.paste(meta[v],(j%w*32,j//w*32))
 im.save(out/(r['id']+'.png'))
 idx.append({'map_id':r['id'],'width_blocks':w,'height_blocks':h,'dimension_status':status,'dimension_candidates':list(dims.keys()),'tiles_rom':hex(r['tiles']),'metatiles_rom':hex(r['metatiles']),'palette_rom':hex(r['palette']),'tile_count':(end-r['tiles'])//32})
(out/'index.json').write_text(json.dumps(idx,ensure_ascii=False,indent=2))
print('Rendered',len(idx))
