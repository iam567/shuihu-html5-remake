"""Differential check: original ROM stage handlers (Genesis Plus GX) vs generated shuihu-html5/dist/js/stage-rules.js.

For each case a work-RAM image is written into the core, the CPU is pointed at `jsr handler; bra *` with interrupts
masked, one frame is run, and the fired event (0x14144 sets FF603D bit 0 and FF6138) plus the scheduler-owned RAM is
read back. The same image is evaluated by the JS handlers through node. Usage:
  SHUIHU_GPX_CORE=/path/genesis_plus_gx_libretro.dylib python3 verify_stage_rules.py [cases_per_stage] [seed]
"""
import ctypes as C,json,os,random,re,struct,subprocess,sys
from pathlib import Path

HERE=Path(__file__).resolve().parent;REPO=HERE.parents[2]
ROM_PATH=next((REPO/'md-game-analysis/baseline').glob('*.md'));ROM=ROM_PATH.read_bytes()
CORE=os.environ.get('SHUIHU_GPX_CORE',str(Path.home()/'Documents/ChatGPT/日常/md-game-analysis/runtime/Genesis-Plus-GX/genesis_plus_gx_libretro.dylib'))
PER=int(sys.argv[1]) if len(sys.argv)>1 else 300;SEED=int(sys.argv[2]) if len(sys.argv)>2 else 1
TABLE=[struct.unpack('>I',ROM[0x120e8+i*4:0x120ec+i*4])[0] for i in range(36)]
UNITS,SLOT=0xffe780,0x40
WATCH={'e1f5':(0xffe1f5,1),'e1d0':(0xffe1d0,1),'e1fc':(0xffe1fc,4),'6019':(0xff6019,1)}

core=C.CDLL(CORE)
class Info(C.Structure):_fields_=[('path',C.c_char_p),('data',C.c_void_p),('size',C.c_size_t),('meta',C.c_char_p)]
SYSDIR=C.c_char_p(str(HERE).encode())
@C.CFUNCTYPE(C.c_bool,C.c_uint,C.c_void_p)
def env(cmd,p):
  if cmd in(9,31):C.cast(p,C.POINTER(C.c_char_p))[0]=SYSDIR.value;return True
  if cmd==10:return C.cast(p,C.POINTER(C.c_int))[0] in(0,1,2)
  if cmd in(3,17):C.cast(p,C.POINTER(C.c_bool))[0]=(cmd==3);return True
  return False
video=C.CFUNCTYPE(None,C.c_void_p,C.c_uint,C.c_uint,C.c_size_t)(lambda *a:None)
sample=C.CFUNCTYPE(None,C.c_int16,C.c_int16)(lambda *a:None)
audio=C.CFUNCTYPE(C.c_size_t,C.c_void_p,C.c_size_t)(lambda p,n:n)
poll=C.CFUNCTYPE(None)(lambda:None)
inp=C.CFUNCTYPE(C.c_int16,C.c_uint,C.c_uint,C.c_uint,C.c_uint)(lambda *a:0)
for name,cb in[('environment',env),('video_refresh',video),('audio_sample',sample),('audio_sample_batch',audio),('input_poll',poll),('input_state',inp)]:getattr(core,'retro_set_'+name)(cb)
core.retro_init()
blob=C.create_string_buffer(ROM);info=Info(str(ROM_PATH).encode(),C.cast(blob,C.c_void_p),len(ROM),None)
core.retro_load_game.argtypes=[C.POINTER(Info)];core.retro_load_game.restype=C.c_bool
assert core.retro_load_game(C.byref(info)),'ROM load failed'
core.m68k_set_reg.argtypes=[C.c_int,C.c_uint];core.m68k_get_reg.argtypes=[C.c_int];core.m68k_get_reg.restype=C.c_uint
for _ in range(120):core.retro_run()
ram=(C.c_ubyte*65536).in_dll(core,'work_ram')
boot=bytes(ram[i^1] for i in range(65536))

def run_handler(stage,image):
  img=bytearray(image);img[0x4000:0x400a]=bytes.fromhex('4eb9')+TABLE[stage].to_bytes(4,'big')+bytes.fromhex('60fe0000')
  swapped=bytearray(65536);swapped[0::2]=img[1::2];swapped[1::2]=img[0::2]
  C.memmove(ram,bytes(swapped),65536)
  core.m68k_set_reg(17,0x2700);core.m68k_set_reg(15,0xfff000);core.m68k_set_reg(16,0xff4000)
  core.retro_run()
  pc=core.m68k_get_reg(16)
  after=bytes(ram[i^1] for i in range(65536))
  return pc,after

def constants(stage):
  """Values each handler compares against, keyed by absolute address or by (displacement,size) inside a unit slot."""
  text=(HERE/'listing.asm').read_text();start=text.index(f'@ {TABLE[stage]:08x} =====');body=text[start:text.find('=====',start+30)]
  absv,rel={},{}
  for size,val,addr in re.findall(r'cmpi\.([bwl]) #(-?0x[0-9a-f]+),\(0x([0-9a-f]+)\)\.l',body):absv.setdefault(int(addr,16),set()).add((int(val,0),'bwl'.index(size)))
  for size,val,disp in re.findall(r'cmpi\.([bwl]) #(-?0x[0-9a-f]+),\((?:(0x[0-9a-f]+),)?A2\)',body):rel.setdefault((int(disp or '0',0),{'b':1,'w':2,'l':4}[size]),set()).add(int(val,0))
  return absv,rel

def put(img,addr,size,value):img[addr&0xffff:(addr&0xffff)+size]=(value&((1<<(8*size))-1)).to_bytes(size,'big')

def make_case(rng,stage,absv,rel):
  img=bytearray(boot)
  for slot in range(30):
    base=UNITS+slot*SLOT
    for off in range(64):put(img,base+off,1,rng.choice([0,0,1,2,3,rng.randrange(256)]))
    for (disp,size),vals in rel.items():
      if rng.random()<0.35:put(img,base+disp,size,rng.choice(sorted(vals)))
    if rng.random()<0.4:put(img,base+0x12,2,0)
    if rng.random()<0.3:put(img,base,1,0)
  # Scenario shapes the uniform fill rarely produces: no enemies left, few enemies, one identity spread over slots.
  mode=rng.random()
  if mode<0.25:
    for slot in range(12,30):put(img,UNITS+slot*SLOT,1,0)
  elif mode<0.45:
    keep=rng.sample(range(12,30),rng.randrange(1,4))
    for slot in range(12,30):put(img,UNITS+slot*SLOT,1,rng.choice([1,2,3]) if slot in keep else 0)
  if rng.random()<0.3 and rel:
    (disp,size),vals=rng.choice(sorted(rel.items(),key=str));v=rng.choice(sorted(vals))
    for slot in range(30):
      if rng.random()<0.5:put(img,UNITS+slot*SLOT+disp,size,v)
  for addr,vals in absv.items():
    v,s=rng.choice(sorted(vals));n=[1,2,4][s]
    put(img,addr,n,v if rng.random()<0.5 else v^(rng.randrange(1,1<<(8*n))))
  put(img,0xffe1f5,1,rng.choice([0xff,0,1,2,3,4,5,6,7,8,rng.randrange(256)]))
  put(img,0xffe1d0,1,rng.choice([0,1,2,3,4,5,6,7,8,9,rng.randrange(256)]))
  put(img,0xffe1f7,1,rng.choice([0,1,2,2]));put(img,0xff6102,1,rng.choice([0,1,1]))
  put(img,0xffe1fc,4,rng.getrandbits(32) if rng.random()<0.5 else rng.getrandbits(32)&rng.getrandbits(32)&rng.getrandbits(32))
  for addr in(0xff6310,0xff614f,0xff6085,0xff609a):put(img,addr,1,rng.choice([0,0,0,1]))
  put(img,0xff6019,1,rng.choice([0,0,2,4,6]))
  put(img,0xff603d,1,0);put(img,0xff6138,1,0xee)
  return img

rng=random.Random(SEED);cases=[]
for stage in range(36):
  absv,rel=constants(stage)
  for i in range(PER):
    img=make_case(rng,stage,absv,rel);pc,after=run_handler(stage,img)
    assert pc==0xff4006,f'stage {stage} case {i}: CPU stopped at {pc:x}, handler did not return'
    fired=after[0x603d]&1
    expect={'event':after[0x6138] if fired else None,**{k:int.from_bytes(after[a&0xffff:(a&0xffff)+s],'big') for k,(a,s) in WATCH.items()}}
    lo,hi=0xe000,0xf000
    cases.append({'stage':stage,'ram':img[lo:hi].hex(),'ram6000':img[0x6000:0x6400].hex(),'expect':expect})
core.retro_unload_game();core.retro_deinit()
work=HERE/'verify-cases.json';work.write_text(json.dumps(cases))
res=subprocess.run(['node',str(REPO/'shuihu-html5/tools/run_stage_cases.mjs'),str(work)],capture_output=True,text=True)
if res.returncode:print(res.stderr);sys.exit(1)
got=json.loads(res.stdout);bad=[]
for i,(case,g) in enumerate(zip(cases,got)):
  if g!=case['expect']:bad.append({'index':i,'stage':case['stage'],'expect':case['expect'],'js':g})
fired=sum(1 for c in cases if c['expect']['event'] is not None)
events=sorted({(c['stage'],c['expect']['event']) for c in cases if c['expect']['event'] is not None})
static={}
text=(HERE/'listing.asm').read_text()
for stage,entry in enumerate(TABLE):
  start=text.index(f'@ {entry:08x} =====');body=text[start:text.find('=====',start+30)]
  static[stage]=sorted({int(v,0) for v in re.findall(r'move\.b #(0x[0-9a-f]+),D2b',body)})
seen={}
for c in cases:
  if c['expect']['event'] is not None:seen.setdefault(c['stage'],set()).add(c['expect']['event'])
unseen={s:[hex(v) for v in vals if v not in seen.get(s,set())] for s,vals in static.items()}
unseen={s:v for s,v in unseen.items() if v}
report={'unseenBaseEvents':unseen,'cases':len(cases),'perStage':PER,'seed':SEED,'mismatches':len(bad),'casesFiringEvent':fired,'stageEventPairsObserved':len(events),'firstMismatches':bad[:5]}
(HERE/'verify-report.json').write_text(json.dumps(report,indent=1));work.unlink()
print(json.dumps({k:v for k,v in report.items() if k!='firstMismatches'}),'\n',json.dumps(bad[:3])[:3000])
sys.exit(1 if bad else 0)
