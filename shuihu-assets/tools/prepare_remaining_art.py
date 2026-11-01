"""Prepare complete, ID-addressed remaining art coverage; never submits requests."""
import json,shutil
from pathlib import Path
from PIL import Image
root=Path(__file__).resolve().parents[1]; workspace=root.parent;out=root/'production/batch-004';out.mkdir(exist_ok=True)
c=json.loads((root/'dist/data/catalog.json').read_text());jobs=[]
def add(id,kind,prompt,ref=None,size='1024x1024',**extra):
 j=dict(id=id,kind=kind,style='shared-hd',size=size,**extra)
 if ref:j['reference']=ref
 (out/(id+'.txt')).write_text(prompt);jobs.append(j)
# Source strips remain preserved; extract nine canonical movement poses as an exact reference grid.
for i in c['items']:
 if i['category']!='characters' or i.get('generated'):continue
 src=Image.open(root/'dist'/i['image']).convert('RGB'); ref=Image.new('RGB',(384,384),(255,0,255))
 for f in range(9):
  pose=src.crop((f*32,0,f*32+32,32)).resize((128,128),Image.Resampling.NEAREST);ref.paste(pose,(f%3*128,f//3*128))
 name=i['id']+'-reference.png';ref.save(out/name)
 add(i['id']+'-walk-v2','character',
 '''Use case: identity-preserve. Edit target: the supplied ORIGINAL 3 by 3 walking pose sheet. Produce a modern crisp JRPG pixel-art sprite sheet, EXACTLY 3 columns and 3 rows, nine equal square cells, canvas 1024 by 1024. Divide canvas into three equal columns and three equal rows. Match each original cell's pose and facing. Row 1 FRONT FACING CAMERA: idle, left foot forward, right foot forward. Row 2 BACK FACING CAMERA: idle, left foot forward, right foot forward. The three back views MUST show the back of the head and garment; NO eyes, face or chest visible. Row 3 SIDE PROFILE FACING LEFT: idle, left foot forward, right foot forward. All nine are the SAME CHARACTER with identical clothing, hair, weapon and proportions. Side will be mirrored by code. Preserve original small character proportions and readable silhouette, refine clustered pixel shading, no blur, no realistic rendering. Whole body and feet visible; constant size and centered origin, feet on the same relative baseline in each cell, 48 pixel margins. Preserve reference identity and colors; do not invent a new hero. Uniform flat pure magenta #ff00ff background, no shadows extending beyond the character, no grid lines, no text, no labels, no extra poses, no attack poses, no blue/red color variants. Do not copy the front face into the back row. This is a game animation asset, not an illustration.''',name,'1024x1024',sourceId=i['id'],frameCount=9,columns=3,rows=3,sourceExtraFrames=i['details']['frameCount']-9)
for i in c['items']:
 if i['category']!='portraits' or i.get('generated'):continue
 if i['id'] in ['portrait-160138','portrait-1605b8']:continue
 name=i['id']+'-reference.png';shutil.copyfile(root/'dist'/i['image'],out/name)
 add(i['id']+'-hd','portrait',
 'Use case: identity-preserve. Edit target: the supplied original Chinese historical RPG portrait. Redraw this SAME person as a polished modern JRPG portrait with clean crisp hand-painted shading and refined readable shapes. Preserve age, gender presentation, head shape, hairstyle, headwear, outfit, distinctive facial features, expression, original palette, facing direction, and square bust crop. Do not turn every character into a young pretty hero; retain elderly, rugged, comic or stern traits when present. One portrait only, no text, numbers, labels or frame, no additional faces. Calm neutral ivory backdrop. Identity fidelity is more important than adding detail.',name,sourceId=i['id'])
a=json.loads((workspace/'shuihu-html5/dist/data/assets.json').read_text());u=json.loads((workspace/'shuihu-html5/dist/data/unicode.json').read_text())['glyphs'];rows=json.loads((workspace/'md-game-analysis/logic/skills_items_142.json').read_text());active={i['id'] for i in rows if not i['all_zero']}
names=[]
for item in a['item_skill_names']:
 if item['id']==0:continue
 name=''.join(u.get(f"{t['bank']}:{t['code']}",'') for t in item['tokens'] if t['type']=='glyph').strip()
 if name:names.append({'id':item['id'],'name':name})
# Already produced 128..142 icons; regenerate neither names nor pixels unnecessarily.
remaining=[i for i in names if i['id']<128]
for n in range(0,len(remaining),16):
 chunk=remaining[n:n+16];id=f'items-{chunk[0]["id"]:03d}-{chunk[-1]["id"]:03d}-hd'
 listing='; '.join(f"cell {k+1}: item #{v['id']} {v['name']}" for k,v in enumerate(chunk))
 add(id,'item-icons',f'''Create a production inventory icon atlas for a Chinese historical JRPG, exactly 4 columns by 4 rows, equal 256x256 cells in a 1024x1024 canvas. {len(chunk)} distinct icons in reading order; any remaining cells empty. {listing}. Interpret each name visually: weapons show the actual named weapon with distinct material, silhouette and ornament; books show bound manuals or scrolls with symbolic cover motifs; footwear, charms and herbs show the specific object. No readable writing, no letters, no numbers, no captions, no printed cell borders. Every icon centered with generous 32 pixel margins, contained entirely in its cell. Consistent modern JRPG item illustration, crisp hand-painted forms, tasteful highlights, clearly distinguish every item. Flat uniform pure magenta #ff00ff background for later separation. Do not combine cells, omit items, swap order, or add characters.''',items=chunk,columns=4,rows=4)
ui=[('dialogue','A wide dialogue panel with an empty square portrait recess on the left and a large calm empty text area on the right. Landscape 1536x1024; single panel centered with 100px margins.'),('shop','One tall shop inventory panel with empty header, six generous blank item rows with square icon recesses, and an empty bottom purchase bar. No illustrated goods, all text areas blank.'),('inventory','One tall inventory panel with empty header, a regular 4 by 4 grid of empty item slots, and an empty description area at bottom.'),('character-status','One character status panel, empty portrait recess, empty name banner, six blank statistic rows and two empty equipment slots.'),('settings','One settings panel with empty header, three wide blank selection cards for art styles, two blank control-mode cards, and footer area. No actual controls or text burned in.'),('battle','Battle HUD components: one wide empty character HP panel, one action command panel, one selected-target frame, one tiny turn-order frame. Separate with wide gutters; no numbers or lettering.'),('buttons','Touch-control component sheet: four wide rounded buttons in normal, pressed, selected and disabled states; a circular close-button rim WITHOUT any cross; a selection highlight and a quantity stepper plate without symbols. Separate components with ample space.'),('save-load','One save/load panel with three large empty save slots, portrait recess and empty text area in each slot, blank header and footer.')]
for id,desc in ui:
 add('ui-'+id+'-hd','interface','Use case: ui-mockup. Production game interface artwork. '+desc+' Chinese historical JRPG style matching jade green, warm ivory parchment, dark wood and restrained antique gold. Beautiful subtle carved corner ornaments; uncluttered flat inner text areas for later real Unicode fonts and touch controls. Crisp polished 2D artwork, orthographic flat view, not a perspective screenshot. No text, numbers, runes, logo or watermark. Uniform magenta #ff00ff outside the isolated panels. Do not draw characters or background scenes. Keep all components fully inside canvas.',size='1536x1024' if id in ['dialogue','battle','buttons'] else '1024x1024',sourceId='ui-'+id)
# Start with corrected protagonist, all item sheets and UI so each category advances.
jobs.sort(key=lambda j: (0 if j['id'].startswith('character-100400') else 1 if j['kind']=='item-icons' else 2 if j['kind']=='interface' else 3 if j['kind']=='portrait' else 4,j['id']))
(out/'jobs.json').write_text(json.dumps(jobs,ensure_ascii=False,indent=2));(out/'item-register.json').write_text(json.dumps({'parameterSlots':len(rows),'nonzeroRows':len(active),'namedItems':len(names),'items':names,'unnamedActiveIds':sorted(active-{i['id'] for i in names})},ensure_ascii=False,indent=2))
from collections import Counter
print(dict(Counter(j['kind'] for j in jobs)),len(jobs),'jobs; named items',len(names))
