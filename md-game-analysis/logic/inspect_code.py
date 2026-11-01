from pathlib import Path
from capstone import *
import sys
r=Path(__file__).resolve().parents[1]; b=next((r/'baseline').glob('*.md')).read_bytes()
c=Cs(CS_ARCH_M68K,CS_MODE_BIG_ENDIAN|CS_MODE_M68K_000);c.skipdata=True
start=int(sys.argv[1],16) if len(sys.argv)>1 else 0
end=int(sys.argv[2],16) if len(sys.argv)>2 else 0x29400
for i in c.disasm(b[start:end],start):print(f'{i.address:06X} {i.bytes.hex():24} {i.mnemonic:10} {i.op_str}')
