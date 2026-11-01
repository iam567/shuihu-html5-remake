import ctypes as C,json,sys,wave,hashlib
from pathlib import Path
from PIL import Image
ROOT=Path(__file__).resolve().parent
ROM=ROOT.parent/'baseline/水浒传 (繁) (川普科技)(16Mb).md'
core=C.CDLL(str(ROOT/'Genesis-Plus-GX/genesis_plus_gx_libretro.dylib'))
class Info(C.Structure):_fields_=[('path',C.c_char_p),('data',C.c_void_p),('size',C.c_size_t),('meta',C.c_char_p)]
class Var(C.Structure):_fields_=[('key',C.c_char_p),('value',C.c_char_p)]
class Geometry(C.Structure):_fields_=[('base_width',C.c_uint),('base_height',C.c_uint),('max_width',C.c_uint),('max_height',C.c_uint),('aspect_ratio',C.c_float)]
class Timing(C.Structure):_fields_=[('fps',C.c_double),('sample_rate',C.c_double)]
class AV(C.Structure):_fields_=[('geometry',Geometry),('timing',Timing)]
opts={b'genesis_plus_gx_region_detect':b'ntsc-j',b'genesis_plus_gx_system_hw':b'sega_md',b'genesis_plus_gx_ym2612':b'mame',b'genesis_plus_gx_audio_filter':b'disabled'}
state={'fmt':0,'buttons':set(),'frame':None,'audio':[],'n':0}
dirbytes=str(ROOT/'saves').encode();(ROOT/'saves').mkdir(exist_ok=True)
@C.CFUNCTYPE(C.c_bool,C.c_uint,C.c_void_p)
def env(cmd,p):
 if cmd in [9,31]:C.cast(p,C.POINTER(C.c_char_p))[0]=dirbytes;return True
 if cmd==10:state['fmt']=C.cast(p,C.POINTER(C.c_int))[0];return state['fmt'] in (0,1,2)
 if cmd==15:
  v=C.cast(p,C.POINTER(Var)).contents
  if v.key in opts:v.value=opts[v.key];return True
  v.value=None
  return False
 if cmd in [3,17]:C.cast(p,C.POINTER(C.c_bool))[0]=(cmd==3);return True
 if cmd==52:C.cast(p,C.POINTER(C.c_uint))[0]=0;return True
 if cmd==(47|0x10000):C.cast(p,C.POINTER(C.c_int))[0]=3;return True
 return False
@C.CFUNCTYPE(None,C.c_void_p,C.c_uint,C.c_uint,C.c_size_t)
def video(p,w,h,pitch):
 if p:state['frame']=(C.string_at(p,h*pitch),w,h,pitch)
@C.CFUNCTYPE(None,C.c_int16,C.c_int16)
def sample(l,r):pass
@C.CFUNCTYPE(C.c_size_t,C.c_void_p,C.c_size_t)
def audio(p,n):state['audio'].append(C.string_at(p,n*4));return n
@C.CFUNCTYPE(None)
def poll():pass
@C.CFUNCTYPE(C.c_int16,C.c_uint,C.c_uint,C.c_uint,C.c_uint)
def inp(port,device,index,id):return int(port==0 and id in state['buttons'])
for name,cb in [('environment',env),('video_refresh',video),('audio_sample',sample),('audio_sample_batch',audio),('input_poll',poll),('input_state',inp)]:getattr(core,'retro_set_'+name)(cb)
core.retro_init()
blob=C.create_string_buffer(ROM.read_bytes());info=Info(str(ROM).encode(),C.cast(blob,C.c_void_p),len(blob)-1,None)
core.retro_load_game.argtypes=[C.POINTER(Info)];core.retro_load_game.restype=C.c_bool
assert core.retro_load_game(C.byref(info)),'ROM load failed'
core.retro_set_controller_port_device(0,1)
av=AV();core.retro_get_system_av_info(C.byref(av))
core.retro_serialize_size.restype=C.c_size_t
core.retro_serialize.argtypes=[C.c_void_p,C.c_size_t];core.retro_serialize.restype=C.c_bool
core.retro_unserialize.argtypes=[C.c_void_p,C.c_size_t];core.retro_unserialize.restype=C.c_bool
names={'b':0,'y':1,'select':2,'start':3,'up':4,'down':5,'left':6,'right':7,'a':8,'x':9,'l':10,'r':11}
def save(label,out):
 path=out/label;path.mkdir(parents=True,exist_ok=True)
 if state['frame']:
  raw,w,h,pitch=state['frame'];pix=bytearray()
  for y in range(h):
   for x in range(w):
    if state['fmt']==1:
     i=y*pitch+x*4;pix+=bytes((raw[i+2],raw[i+1],raw[i]))
    else:
     i=y*pitch+x*2;v=raw[i]|raw[i+1]<<8
     if state['fmt']==2:pix+=bytes((((v>>11)&31)*255//31,((v>>5)&63)*255//63,(v&31)*255//31))
     else:pix+=bytes((((v>>10)&31)*255//31,((v>>5)&31)*255//31,(v&31)*255//31))
  Image.frombytes('RGB',(w,h),bytes(pix)).save(path/'screen.png')
 for sym,n in [('work_ram',65536),('vram',65536),('cram',128),('vsram',128),('reg',32),('zram',8192),('sat',1024)]:
  data=bytes((C.c_ubyte*n).in_dll(core,sym));(path/(sym+'.bin')).write_bytes(data)
 size=core.retro_serialize_size();buf=C.create_string_buffer(size);assert core.retro_serialize(buf,size);(path/'state.bin').write_bytes(buf.raw)
 (path/'metadata.json').write_text(json.dumps({'label':label,'frame':state['n'],'fps':av.timing.fps,'sample_rate':av.timing.sample_rate,'pixel_format':state['fmt'],'rom_sha256':hashlib.sha256(blob.raw[:-1]).hexdigest(),'memory_byte_order':'core-native; 68000 work_ram/vram words may be byte-swapped on little endian host'},indent=2))
 print('saved',path,flush=True)
conf=json.loads(Path(sys.argv[1]).read_text());out=ROOT/conf.get('output','captures');out.mkdir(exist_ok=True)
if conf.get('load_state'):
 b=Path(conf['load_state']).read_bytes();buf=C.create_string_buffer(b);assert core.retro_unserialize(buf,len(b))
core.m68k_get_reg.argtypes=[C.c_int];core.m68k_get_reg.restype=C.c_uint
core.m68k_set_reg.argtypes=[C.c_int,C.c_uint]
def putram(address,data):
 mem=(C.c_ubyte*65536).in_dll(core,'work_ram')
 for j,v in enumerate(data):mem[((address+j)&65535)^1]=v
def call(addr):
 pc=core.m68k_get_reg(16);sp=(core.m68k_get_reg(15)-4)&0xffffff
 putram(sp,pc.to_bytes(4,'big'));core.m68k_set_reg(15,sp);core.m68k_set_reg(16,addr)
for action in conf['actions']:
 if action.get('load_state'):
  b=Path(action['load_state']).read_bytes();buf=C.create_string_buffer(b);assert core.retro_unserialize(buf,len(b));state['audio']=[]
 if action.get('freeze'):
  putram(0xff4000,bytes.fromhex('60fe'));core.m68k_set_reg(16,0xff4000)
 if 'sound_command' in action:
  putram(0xff6d00,int(action['sound_command']).to_bytes(2,'big'));call(0x1e41d4)
 if 'call' in action:call(int(action['call'],0))
 if action.get('clear_audio'):state['audio']=[]
 if 'poke' in action:
  mem=(C.c_ubyte*65536).in_dll(core,'work_ram')
  for a,v in action['poke'].items():mem[int(a,0)^1]=v
 state['buttons']={names[x] for x in action.get('buttons',[])}
 for _ in range(action.get('frames',1)):core.retro_run();state['n']+=1
 if action.get('save'):save(action['save'],out)
 if action.get('audio'):
  with wave.open(str(out/action['audio']),'wb') as f:f.setnchannels(2);f.setsampwidth(2);f.setframerate(round(av.timing.sample_rate));f.writeframes(b''.join(state['audio']))
  state['audio']=[]
core.retro_unload_game();core.retro_deinit()
