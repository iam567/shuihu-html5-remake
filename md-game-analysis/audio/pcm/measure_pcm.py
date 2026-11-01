import ctypes as C,json,sys,collections
from pathlib import Path
P=Path(__file__).resolve().parents[2]
run=P/'runtime/run_rom.py'
ns={'__file__':str(run),'__name__':'pcm_probe'}
exec(run.read_text().split('conf=json.loads')[0],ns)
core=ns['core'];state=ns['state'];zr=(C.c_ubyte*8192).in_dll(core,'zram')
class ZRegs(C.Structure):
 _fields_=[('regs',C.c_uint32*13),('flags',C.c_uint8*11),('cycles',C.c_uint32),('daisy',C.c_void_p),('irq',C.c_void_p)]
z=ZRegs.in_dll(core,'Z80')
Write=C.CFUNCTYPE(None,C.c_uint,C.c_ubyte)
slot=C.c_void_p.in_dll(core,'z80_writemem');orig=Write(slot.value);events=[]
@Write
def hook(a,d):
 if a==0x4001:events.append((z.cycles,d,z.regs[0]&65535))
 orig(a,d)
base=(P/'runtime/audio-test/music0/state.bin').read_bytes()
core.m68k_set_reg.argtypes=[C.c_int,C.c_uint]
mem=(C.c_ubyte*65536).in_dll(core,'work_ram')
normal="--normal" in sys.argv
if normal: sys.argv.remove("--normal")
report=[]
for sid in (list(map(int,sys.argv[1:])) if len(sys.argv)>1 else range(2,128)):
 buf=C.create_string_buffer(base);assert core.retro_unserialize(buf,len(base))
 slot.value=C.cast(hook,C.c_void_p).value
 # Freeze 68k in a local self-loop; run the unchanged Z80 driver with a raw DAC command.
 mem[0x4000^1]=0x60;mem[0x4001^1]=0xfe;core.m68k_set_reg(16,0xff4000)
 zr[0x21]=0;zr[0x20]=sid if normal else sid|0x80;zr[0x22]=0;events.clear();core.retro_run()
 filtered=[e for e in events if e[2]==0x185]
 ds=collections.Counter(b[0]-a[0] for a,b in zip(filtered,filtered[1:]) if b[0]>a[0])
 report.append({'sample_id':sid,'dac_event_count':len(filtered),'interval_master_cycles':dict(ds),'first_64_values':[e[1] for e in filtered[:64]],'all_event_pc_counts':dict(collections.Counter(e[2] for e in events)),'z80_init_30_35':bytes(zr[0x30:0x36]).hex()})
 state['audio']=[]
slot.value=C.cast(orig,C.c_void_p).value
core.retro_unload_game();core.retro_deinit()
(P/('audio/pcm/measured-timing-normal.json' if normal else 'audio/pcm/measured-timing.json')).write_text(json.dumps(report,indent=2));print(json.dumps(report[:2],indent=2))
