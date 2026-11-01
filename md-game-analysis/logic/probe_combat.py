from pathlib import Path
import json
r=Path(__file__).resolve().parents[1]
s=(r/'runtime/run_rom.py').read_text().replace("ROOT=Path(__file__).resolve().parent",f"ROOT=Path({str(r/'runtime')!r})")
s=s.replace("print('saved',path,flush=True)","(path/'registers.json').write_text(json.dumps({str(i):core.m68k_get_reg(i) for i in range(18)},indent=2)); print('saved',path,flush=True)")
s=s.replace("if 'call' in action:call(int(action['call'],0))", "if 'registers' in action:\n  for regid,val in action['registers'].items():core.m68k_set_reg(int(regid),val)\n if 'call' in action:call(int(action['call'],0))")
s=s.replace("print('saved',path,flush=True)", "(path/'sram-core-struct.bin').write_bytes(bytes((C.c_ubyte*65552).in_dll(core,'sram'))); print('saved',path,flush=True)")
exec(compile(s,str(r/'runtime/run_rom.py'),'exec'))
