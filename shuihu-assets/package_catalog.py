from pathlib import Path
from PIL import Image
import json,shutil,hashlib,sys,struct
sys.path.insert(0,str(Path(__file__).resolve().parent.parent/"md-game-analysis/graphics"))
from extract_graphics import rom,tiles,palette,tile_image
G=(Path(__file__).resolve().parent.parent/'md-game-analysis/graphics');D=Path(__file__).resolve().parent/'dist';A=D/'assets'
def read(p):return json.loads((G/p).read_text())
def copy(src,name):
 dest=A/name;shutil.copy2(src,dest)
 with Image.open(src) as im:w,h=im.size
 assert hashlib.sha256(src.read_bytes()).digest()==hashlib.sha256(dest.read_bytes()).digest()
 return {'image':'assets/'+name,'width':w,'height':h,'sourcePath':str(src),'sha256':hashlib.sha256(src.read_bytes()).hexdigest(),'bytes':dest.stat().st_size}
def item(id,cat,name,src,filename,confidence,details):
 e={'id':id,'category':cat,'name':name,**copy(src,filename),'confidence':confidence,'details':details};items.append(e);return e
derived=Path(__file__).resolve().parent/'derived';derived.mkdir(exist_ok=True)
def render_bank(r,bid):
 data,end=tiles(int(r['tiles_rom'],16));full=bytes(512*32)+data;pal=palette(int(r['palette_rom'],16));maxid=max(int(x) for x in r['metatile_words']);im=Image.new('RGBA',(512,((maxid+16)//16)*32))
 for rawid,words in r['metatile_words'].items():
  n=int(rawid)
  for j,w in enumerate(words):im.paste(tile_image(full,w&2047,pal,w),(n%16*32+j%4*8,n//16*32+j//4*8))
 im.save(derived/(bid+'.png'))
 for pp in range(2):
  atlas=Image.new('RGBA',(256,((len(data)//32+31)//32)*8))
  for n in range(len(data)//32):atlas.paste(tile_image(data,n,pal,pp<<13),(n%32*8,n//32*8))
  atlas.save(derived/(bid+f'-tiles-palette-{pp}.png'))
items=[];bankrows=read('map_banks/index.json');bankid=lambda r:'bank-'+r['name'].replace('_','-')+'-'+r['palette_rom'][2:].zfill(6)
last_palette={r['name']:r['palette_rom'] for r in bankrows}
maptobank={mid:bankid(r) for r in bankrows for mid in r['maps']};banklinks=[]
for r in read('maps/index.json'):
 mid=r['map_id'];e=item('map-'+mid,'maps','地图 '+mid,G/'maps'/f'{mid}.png',f'map-{mid}.png',{'level':'high' if mid=='0106' or r['dimension_status'].startswith('explicit') else 'medium-high','basis':r['dimension_status'],'limit':'多数地图尺寸来自静态脚本与出生记录关联，未逐张运行验证。'}, {'mapId':mid,'widthTiles':r['width_blocks'],'heightTiles':r['height_blocks'],'tileSize':32,'bankId':maptobank[mid],'tilesRom':r['tiles_rom'],'metatilesRom':r['metatiles_rom'],'paletteRom':r['palette_rom']});e['bankId']=maptobank[mid]
for r in bankrows:
 bid=bankid(r);previews=[];render_bank(r,bid)
 for p in range(2):previews.append({'palette':p,**copy(derived/(bid+f'-tiles-palette-{p}.png'),f'{bid}-tiles-palette-{p}.png')})
 e=item(bid,'map-banks','组合图块 '+r['name'],derived/(bid+'.png'),bid+'.png',{'level':'high','basis':'指针、图块属性和地图拼图相互对应','limit':'此图集包含已使用组合块；透明空格不代表待重画图片。'},{'maps':r['maps'],'mapCount':len(r['maps']),'baseTileCount':r['tile_count'],'metatileCount':len(r['metatile_words']),'metatileSize':32,'tileSize':8,'tilesRom':r['tiles_rom'],'metatilesRom':r['metatiles_rom'],'paletteRom':r['palette_rom'],'paletteRgb':r['palette_rgb']});e['previewPaletteRom']=r['palette_rom'];e['previewPaletteMatchesGroup']=True;e['previewSourceSharedKey']=r['name'];e['derivedFromRom']=True
 if not e['previewPaletteMatchesGroup']:e['confidence']={'level':'partial','basis':'原资源组关系已确认；复用现存图集预览','limit':'此现存图集色板为'+last_palette[r['name']]+'，与本组'+r['palette_rom']+'不同。没有生成新图；请用本组完整地图核对配色。'}
 e['mapIds']=r['maps'];e['mapCount']=len(r['maps']);e['baseTilePreviews']=previews;banklinks.append({'id':bid,'mapIds':r['maps'],'mapCount':len(r['maps'])})
for r in read('characters/index.json'):
 bank=r['start'][2:];item('character-'+bank,'characters','人物精灵 '+bank,G/'characters'/f'{bank}_sheet.png',f'character-{bank}.png',{'level':'medium-high','basis':'原指针资源边界与32×32帧排列；主角和阿福已运行匹配','limit':'统一使用开场调色板，其余场景换色及额外帧动作语义未完全验证。'},{'characterIds':r['character_ids'],'bank':bank,'frameCount':r['frame_count_by_pointer_boundary'],'frameWidth':32,'frameHeight':32,'layout':'horizontal','sourceStart':r['start'],'sourceEnd':r['end']})
portraits=read('portraits/index.json');seen=set()
for r in portraits:
 a=r['data_rom'][2:]
 if a in seen:continue
 seen.add(a);aliases=[x['portrait_id'] for x in portraits if x['data_rom']==r['data_rom']];item('portrait-'+a,'portraits','人物头像 '+a,G/'portraits'/r['file'],f'portrait-{a}.png',{'level':'medium-high','basis':'头像指针表及48×48列序图块；阿福已逐字节运行匹配','limit':'其它场景调色变化未全面验证。'},{'portraitIds':aliases,'sourceStart':r['data_rom'],'pixelWidth':48,'pixelHeight':48})
for r in read('fonts/index.json'):
 b=r['bank'];item(f'font-{b}','fonts',f'中文字库 {b}',G/'fonts'/f'bank{b}_sheet.png',f'font-{b}.png',{'level':'high','basis':'1bpp展开函数与运行中文字逐字节核对','limit':'带字码标签的总览图；尚未建立校验后的Unicode码表。'},{'bank':b,'glyphCount':r['glyph_count'],'glyphWidth':16,'glyphHeight':16,'sheetColumns':16,'sourceStart':r['start'],'sourceEnd':r['end'],'labelledPreview':True})
for r in read('ui_banks/index.json'):
 a=r['rom'][2:].zfill(6);item('ui-'+a,'ui','界面图块 '+a,G/'ui_banks'/f'{a}_indexed_grayscale.png',f'ui-{a}.png',{'level':'partial','basis':'代码直接调用上传入口，图块边界由终止字确认','limit':'灰度表示像素索引；不是最终配色/拼好的界面。'},{'tileCount':r['tiles'],'tileSize':8,'palette':'indexed-grayscale','sourceStart':r['rom'],'sourceEnd':r['end'],'uploadCallSites':r['call_sites']})
item('title','title','水浒传标题画面',G/'title_reconstructed.png','title.png',{'level':'high','basis':'代码指定图块、调色板、tilemap和文字位置重建','limit':'静态画面，不包含渐变/闪烁时序。'},{'reconstruction':'static title background and menu overlays'})
labels={'maps':'完整地图','map-banks':'地图组合图块','characters':'人物精灵','portraits':'人物头像','fonts':'中文字库','ui':'界面图块','title':'标题画面'};counts={k:sum(x['category']==k for x in items) for k in labels};cats=[{'id':k,'name':v,'count':counts[k]} for k,v in labels.items()]
catalog={'formatVersion':1,'title':'水浒传素材总览','description':'原版素材总览；31组图集按原ROM正确重建，其余复用已解析图片。没有AI重绘，不含ROM或模拟器。','categories':cats,'counts':counts,'totalItems':len(items),'items':items,'mapToBank':{'map-'+k:v for k,v in maptobank.items()},'banks':banklinks,'notes':['31组原版地图图集按图块、组合块、调色板三元组唯一命名，已修复旧输出异色板命名冲突。技术性原ROM图集重建，没有AI生图。','完整地图是整体预览，重绘复用素材优先查看组合图块和基础图块。','人物与头像按独立源资源去重，aliases保留原始ID复用关系。','字体是带码位标签的原字库预览；UI灰度图需要后续配色和布局确认。'],'verification':{'copiedByteIdentical':True,'romIncluded':False,'aiImagesGenerated':False,'technicalBankPreviewsRendered':31,'mapLinks':len(maptobank),'uniqueCopiedImages':len(list(A.glob('*.png'))),'mapBankCombinations':31,'distinctRenderedMapBankPreviewSets':31,'assetBytes':sum(p.stat().st_size for p in A.glob('*.png'))}}
assert counts=={'maps':116,'map-banks':31,'characters':60,'portraits':40,'fonts':8,'ui':40,'title':1},counts
assert len(maptobank)==116 and sum(r['mapCount'] for r in banklinks)==116
assert all((D/x['image']).is_file() for x in items)
(D/'data/catalog.json').write_text(json.dumps(catalog,ensure_ascii=False,indent=2));print(counts,catalog['verification'])
