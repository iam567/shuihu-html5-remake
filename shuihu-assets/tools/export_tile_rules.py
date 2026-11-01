import json
from pathlib import Path
from collections import Counter,defaultdict
root=Path(__file__).resolve().parents[1]
catalog=json.loads((root/'dist/data/catalog.json').read_text())
assets=json.loads((root.parent/'shuihu-html5/dist/data/assets.json').read_text())
by_id={i['details']['mapId']:i for i in catalog['items'] if i['category']=='maps'}
banks=defaultdict(dict);maps={}
for m in assets['maps']:
 bank=by_id[m['id']]['bankId'];maps[m['id']]={'width':m['widthTiles'],'height':m['heightTiles'],'graphics':m['graphicLayer'],'logic':m['collision'],'bankId':bank}
 for idx,(tile,logic) in enumerate(zip(m['graphicLayer'],m['collision'])):
  r=banks[bank].setdefault(str(tile),{'values':Counter(),'maps':set(),'examples':[]})
  r['values'][str(logic)]+=1;r['maps'].add(m['id'])
  if len(r['examples'])<8:r['examples'].append({'mapId':m['id'],'x':idx%m['widthTiles'],'y':idx//m['widthTiles'],'logic':logic})
for tiles in banks.values():
 for row in tiles.values():row['values']=dict(row['values']);row['maps']=sorted(row['maps'])
out={'version':1,'scope':'原始地图格数据。探索通行语义已恢复；战场地形和各兵种通行仍待核对。动态剧情覆写及NPC阻挡不在此静态预览内。','maps':maps,'banks':dict(banks)}
(root/'dist/data/tile-rules.json').write_text(json.dumps(out,ensure_ascii=False,separators=(',',':')))
print('linked maps',len(maps),'resource groups',len(banks),'placed block variants',sum(len(v) for v in banks.values()))
