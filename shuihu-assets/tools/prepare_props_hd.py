"""HD redraw jobs for the map props (opcode 0x3D, shuihu-html5/dist/data/props.json), one job per distinct picture.

Each job's first reference is the original prop at nearest-neighbour scale, centred on flat magenta; people use the HD
walk-sheet style reference (production/sprites-hd-1/style-ref.png, copied in on the VPS) as the second reference, objects
the surrounding hd2d map. The cave on 0A07 is part of the scenery, so it is redrawn inside its own map crop and cut back
out later along its original outline. Prompts spell out everything that must survive (pose, arrows, ropes, blood) so the
redraw cannot turn into something else; every result is reviewed against the original before use.
Writes production/props-hd-1/{refs, prompts, jobs.json}. Nothing is submitted.
Usage: python3 tools/prepare_props_hd.py
"""
import json
from pathlib import Path
from PIL import Image

ROOT=Path(__file__).resolve().parents[1];GAME=ROOT.parent/'shuihu-html5/dist';OUT=ROOT/'production/props-hd-1'
MAGENTA=(255,0,255,255)
COMMON=('Flat pure magenta #ff00ff background everywhere around the subject, no ground, no cast shadow, no text, no frame, '
        'no grid lines. One single subject, centred, filling most of the canvas.')
PERSON=('Use case: faithful game sprite redraw. The first image is an original retro pixel sprite; redraw exactly that sprite as one '
        'high-definition hand-painted game sprite in the art style of the second image (clean modern Chinese-fantasy JRPG, crisp dark '
        'outlines, soft cel shading, no pixel art, no visible pixels). Copy the first image faithfully: the same pose and silhouette, the '
        'same viewing angle, the same outfit colours, the same objects in the same places, nothing added and nothing left out. ')
OBJECT=('Use case: faithful game prop redraw. The first image is an original retro pixel sprite of an object; redraw exactly that '
        'object in high definition in the art style of the second image (a detailed modern HD-2D pixel-art game map, crisp clustered '
        'shading, warm daylight from the top left), seen from the same three-quarter top-down angle as the original. Copy the first '
        'image faithfully: the same shape, proportions, parts and colours, nothing added and nothing left out. ')
# bit -> (what it shows, canvas size); duplicates (3 = 2, 10 = 5, 13/14 = 12) reuse the picture.
JOBS={
 0:('object','A small two-wheeled wooden handcart carrying four big round brown wine jars with red cloth-covered lids tied with '
    'cord, each jar with a red diamond paper label; two jars in front, two behind; wooden shafts pointing left, one big spoked '
    'wooden wheel visible at the front right.','1536x1024'),
 1:('object','The same small two-wheeled wooden handcart as a wine cart, now carrying four big round wine jars lying open: their lids '
    'are gone and the clear blue wine shows inside each open jar mouth; two jars in front, two behind; wooden shafts pointing left, '
    'one big spoked wooden wheel at the front right.','1536x1024'),
 2:('person','A young woman in a blue robe with a black hair bun, collapsed kneeling on the ground and slumped forward, head bowed so '
    'her face is hidden, one arm reaching forward to the lower left; she has been shot by an arrow: keep the short arrow exactly '
    'where the original shows it at her left hand, and the small red blood drops on the ground around her. She is not standing, '
    'not fighting and holds no weapon.','1024x1024'),
 4:('person','A stout official seen from the front, seated upright and still, in a wide golden-yellow robe with a small red-and-white '
    'collar detail, wearing a tall black-and-white striped official hat with a gold top; plump face, arms resting at his sides, '
    'black boots showing below the robe.','1024x1024'),
 5:('object','A small round green jade ring with a gold rim, with a short red silk tassel hanging from its lower left, lying on the '
    'floor; two tiny red drops beside it.','1024x1024'),
 6:('object','A wooden prisoner cage cart: a box cage of vertical wooden bars with a plank roof and floor, on a two-wheeled cart with '
    'one big spoked wooden wheel at the front right and wooden shafts pointing left. The cage is empty.','1536x1024'),
 7:('person','A man seen from the front with his hair in a topknot, standing with his whole torso and arms tightly bound by many '
    'coils of brown rope wound round and round his body from chest to waist, arms pinned inside the ropes; robe with a white '
    'collar; stern face.','1024x1024'),
 8:('person','A wounded man in a blue robe with red and gold trim, kneeling on the ground facing the viewer, head with a topknot, mouth '
    'bleeding; two arrows stick up out of his back behind his shoulders, one on each side (the right one with red fletching); '
    'red blood splashes on the ground around his knees.','1024x1024'),
 9:('person','A captive man in a blue robe with red and white panels and green boots, standing facing the viewer, both arms raised out '
    'to the sides at head height, each wrist locked in a black iron shackle with prongs, hanging as if chained between two posts; '
    'tousled grey-black hair with a small topknot.','1536x1024'),
 11:('cave','','1024x1024'),
 12:('object','A closed book with a red cover and a cream-yellow title slip on the front (the slip is blank, no characters), seen '
    'standing face-on, the white page edges showing at the bottom.','1024x1024'),
 15:('person','A nobleman in a red robe patterned with gold and a red hat, kneeling on the ground and bent forward in pain with his head '
    'bowed, one hand clutching the ground; a yellow sash end flies out to the right; blue under-robe showing at the knees; red blood '
    'drops on the ground beside him. Seen from the front, a little from above.','1024x1024'),
 16:('person','The same nobleman in a red robe patterned with gold and a red hat, now collapsed lying face-down on the ground with his '
    'body stretched to the right, motionless, a pool of red blood spreading under and around him. Seen from a three-quarter '
    'top-down angle.','1536x1024'),
}

def reference(img,size):
  W,H=map(int,size.split('x'));k=max(1,min(int(W*0.8)//img.width,int(H*0.8)//img.height))
  big=img.resize((img.width*k,img.height*k),Image.Resampling.NEAREST);canvas=Image.new('RGBA',(W,H),MAGENTA)
  canvas.alpha_composite(big,((W-big.width)//2,(H-big.height)//2));return canvas.convert('RGB')

def map_crop(p,half=96):
  m=Image.open(GAME/f"assets/maps-hd/hd2d/{p['map']}.webp").convert('RGB');cx,cy=(p['x']+p['w']//2)*4,(p['y']+p['h']//2)*4
  x0,y0=max(0,min(m.width-2*half*4,cx-half*4)),max(0,min(m.height-2*half*4,cy-half*4))
  return m.crop((x0,y0,x0+half*8,y0+half*8)),(x0,y0)

if __name__=='__main__':
  OUT.mkdir(parents=True,exist_ok=True);props={p['bit']:p for p in json.loads((GAME/'data/props.json').read_text())['props']}
  jobs=[];meta={}
  for bit,(kind,desc,size) in JOBS.items():
    p=props[bit];img=Image.open(GAME/p['image']).convert('RGBA');jid=f'prop-{bit:02d}'
    if kind=='cave':
      crop,(x0,y0)=map_crop(p,64);big=img.resize((img.width*4,img.height*4),Image.Resampling.NEAREST)
      crop=crop.convert('RGBA');crop.alpha_composite(big,(p['x']*4-x0,p['y']*4-y0));crop=crop.resize((1024,1024),Image.Resampling.NEAREST)
      crop.convert('RGB').save(OUT/f'{jid}-ref.png');refs=[f'{jid}-ref.png'];meta[jid]={'crop':[x0,y0,512,512]}
      prompt=('Use case: faithful map repair. The image is a detailed HD-2D pixel-art game map of a rocky cliff, with an old low-'
        'resolution pixel cave mouth pasted into its middle. Redraw ONLY the pasted cave mouth in the same detailed HD-2D style, '
        'lighting and rock texture as the cliff around it, so it blends in: the same arched opening in the same place and of the same '
        'size and outline, pitch-dark inside, with the same brown earth floor running out of it and mossy yellow-green rock around its '
        'rim. Keep everything outside the cave mouth pixel-for-pixel unchanged. No text, no people, same canvas size.')
    else:
      reference(img,size).save(OUT/f'{jid}-ref.png')
      if kind=='person':style='style-ref.png';prompt=PERSON+desc+' '+COMMON
      else:
        crop,_=map_crop(p,48);crop.save(OUT/f'{jid}-style.png');style=f'{jid}-style.png';prompt=OBJECT+desc+' '+COMMON
      refs=[f'{jid}-ref.png',style]
    (OUT/f'{jid}.txt').write_text(prompt)
    jobs.append({'id':jid,'kind':'prop-'+kind,'references':refs,'size':size,'sourceId':bit})
  (OUT/'jobs.json').write_text(json.dumps(jobs,indent=2));(OUT/'meta.json').write_text(json.dumps(meta))
  print(len(jobs),'jobs')
