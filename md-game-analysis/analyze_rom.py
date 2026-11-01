from pathlib import Path
import json,hashlib,struct,collections
from capstone import *
root=Path(__file__).parent
p=Path('/Users/taoo/Downloads/05a04fef4388020ea303c2c89dccc2bb09c50625ff3872967237dd9173647202.md')
b=p.read_bytes(); c=Cs(CS_ARCH_M68K,CS_MODE_BIG_ENDIAN|CS_MODE_M68K_000)
# Disassemble only declared windows, allowing enough trailing bytes for decoding.
wins=[(0x104,0x188),(0x18a,0x4ba),(0x4ba,0xe40),(0xe40,0x1298),(0x1298,0x1500),(0x273cc,0x27500),(0x27ae8,0x27c20),(0x27fb8,0x28162),(0x1e3a00,0x1e3b00),(0x1e41d4,0x1e42d4),(0x1e7618,0x1e7718)]
lines=[]
for st,en in wins:
 lines.append(f'\n; WINDOW 0x{st:06X}..0x{en:06X} (linear decode; code/data boundaries not guaranteed)')
 for i in c.disasm(b[st:en+16],st):
  if i.address>=en:break
  lines.append(f'{i.address:06X}  {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}')
(root/'selected-disassembly.txt').write_text('\n'.join(lines))
vec=list(struct.unpack('>64I',b[:256]))
blocks=[]
for st in range(0,len(b),0x10000):
 part=b[st:st+0x10000];count=collections.Counter(part)
 blocks.append({'offset':hex(st),'zero_fraction':round(count[0]/len(part),3),'ff_fraction':round(count[255]/len(part),3),'distinct_bytes':len(count)})
r={'path':str(p),'size':len(b),'sha256':hashlib.sha256(b).hexdigest(),'initial_sp':hex(vec[0]),'reset_pc':hex(vec[1]),'vectors':[hex(x) for x in vec],'vdp_init_words':[hex(x) for x in struct.unpack('>19H',b[0x293c4:0x293c4+38])],'blocks_64k':blocks}
(root/'rom-facts.json').write_text(json.dumps(r,indent=2))
print(json.dumps(r,indent=2))
