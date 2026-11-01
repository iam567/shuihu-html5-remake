from pathlib import Path
import json,shutil
from PIL import Image
SRC=(Path(__file__).resolve().parent.parent/'md-game-analysis');DST=Path(__file__).resolve().parent/'dist'; G=SRC/'graphics';A=DST/'assets';A.mkdir(parents=True,exist_ok=True)
def read(p):return json.loads(p.read_text())
def cp(src,rel):
 dest=DST/rel;dest.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(src,dest);return rel
maps=read(SRC/'logic/maps/maps.json');dims={r['map_id']:r for r in read(G/'maps/index.json')};spawns=read(SRC/'logic/maps/spawn_records.json');spawn_by_id={r['id']:r for r in spawns};candidates=read(SRC/'logic/maps/map_dimensions_candidates.json')
result={'formatVersion':1,'tileSize':32,'pathBase':'dist-root','maps':[],'characters':[],'portraits':[],'dialogues':[],'fonts':{'glyphWidth':16,'glyphHeight':16,'columns':16,'banks':[]},'title':cp(G/'title_reconstructed.png','assets/title.png')}
for r in maps:
 if r['id']=='0000':continue
 d=dims[r['id']];ids=sorted({c['spawn_id'] for c in candidates if c['map_id']==r['id']});entry={'id':r['id'],'widthTiles':d['width_blocks'],'heightTiles':d['height_blocks'],'widthPixels':d['width_blocks']*32,'heightPixels':d['height_blocks']*32,'image':cp(G/'maps'/f"{r['id']}.png",f"assets/maps/{r['id']}.png"),'collision':list((SRC/'logic/maps'/r['layers'][2]['file']).read_bytes()),'graphicLayer':list((SRC/'logic/maps'/r['layers'][1]['file']).read_bytes()),'spawnRecords':[spawn_by_id[s] for s in ids if s in spawn_by_id],'dimensionEvidence':d['dimension_status'],'collisionSemantics':'raw values; interpret using logic collision rules, not boolean'};result['maps'].append(entry)
for r in read(G/'characters/index.json'):
 bank=r['start'][2:];path=cp(G/'characters'/f'{bank}_sheet.png',f'assets/characters/{bank}.png')
 for id in r['character_ids']:result['characters'].append({'id':id,'bank':bank,'frames':r['frame_count_by_pointer_boundary'],'sheet':path,'frameWidth':32,'frameHeight':32,'layout':'horizontal','paletteStatus':'observed start scene palette2; contextual variants not represented'})
result['characters'].sort(key=lambda r:r['id'])
for r in read(G/'portraits/index.json'):
 bank=r['data_rom'][2:];path=f'assets/portraits/{bank}.png'
 if not (DST/path).exists():cp(G/'portraits'/r['file'],path)
 result['portraits'].append({'id':r['portrait_id'],'image':path,'width':48,'height':48})
for r in read(G/'text/dialogues.json'):
 result['dialogues'].append({'id':r['id'],'image':cp(G/'text/dialogue_pages'/f"{r['id']:03d}.png",f"assets/dialogues/{r['id']:03d}.png"),'tokens':r['tokens'],'rawHex':r['raw_hex'],'parseStatus':r['parse_status']})
for r in read(G/'fonts/index.json'):
 n=r['glyph_count'];bank=r['bank'];im=Image.new('RGBA',(256,((n+15)//16)*16))
 for c in range(n):im.paste(Image.open(G/'fonts'/f'bank{bank}_{c:02x}.png'),(c%16*16,c//16*16))
 rel=f'assets/fonts/bank{bank}.png';(DST/rel).parent.mkdir(parents=True,exist_ok=True);im.save(DST/rel);result['fonts']['banks'].append({'bank':bank,'count':n,'sheet':rel,'ink':'black','background':'transparent'})
for key in ['item_skill_names','character_names','job_names']:
 result[key]=read(G/'text'/f'{key}.json');cp(G/'text'/f'{key}.png',f'assets/catalogs/{key}.png')
result['animationFrameLookup']=[3,4,3,5,0,1,0,2,6,7,6,8,6,7,6,8,9,10,11,12,13,14,15,15,16,17,18,18,19,20,21,22]
result['animationNote']='Original ROM 0x138E lookup; indexes beyond bank frame count require separate original-context investigation. Base walking uses states0..15.'
(DST/'data/assets.json').write_text(json.dumps(result,ensure_ascii=False,separators=(',',':')))
# Validate every referenced image, sizes, collision grid, aliases and no ROM carriers.
paths=set();errors=[]
for r in result['maps']:
 if len(r['collision'])!=r['widthTiles']*r['heightTiles']:errors.append('collision '+r['id'])
 if Image.open(DST/r['image']).size!=(r['widthPixels'],r['heightPixels']):errors.append('size '+r['id'])
for category in ['maps','characters','portraits','dialogues']:
 for r in result[category]:paths.add(r.get('image',r.get('sheet')))
paths.add(result['title']);paths.update(r['sheet'] for r in result['fonts']['banks'])
for p in paths:
 if not (DST/p).is_file():errors.append('missing '+p)
assert not errors,errors
assert not list(A.rglob('*.bin')) and not list(A.rglob('*.md'))
summary={'maps':len(result['maps']),'characterIds':len(result['characters']),'uniqueCharacterSheets':len({r['sheet'] for r in result['characters']}),'portraitIds':len(result['portraits']),'uniquePortraits':len({r['image'] for r in result['portraits']}),'dialogues':len(result['dialogues']),'fonts':sum(r['count'] for r in result['fonts']['banks']),'referencedImages':len(paths),'assetBytes':sum(p.stat().st_size for p in A.rglob('*') if p.is_file()),'manifestBytes':(DST/'data/assets.json').stat().st_size,'validationErrors':errors}
(DST/'data/assets-validation.json').write_text(json.dumps(summary,indent=2));print(summary)
