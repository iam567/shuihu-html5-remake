"""Translate the 36 battle-stage handlers (ROM jump table 0x120E8, dispatched by 0x12074) into JavaScript.

Input is the Ghidra listing exported by md-game-analysis/ghidra/ExportStageHandlers.java. Every 68000 instruction
becomes one JS statement on an explicit register/flag model, so branches and flag behaviour stay instruction-exact.
The output never loads the ROM; it reads and writes battle state through the memory interface given by the caller.
"""
import re,struct,json,hashlib
from pathlib import Path

root=Path(__file__).resolve().parents[2]
listing=root/'md-game-analysis/logic/stage_events/listing.asm'
rom=next((root/'md-game-analysis/baseline').glob('*.md')).read_bytes()
out=root/'shuihu-html5/dist/js/stage-rules.js'
TABLE,COUNT,EVENT=0x120e8,36,0x14144

entries=[struct.unpack('>I',rom[TABLE+i*4:TABLE+i*4+4])[0] for i in range(COUNT)]
funcs={};cur=None
for line in listing.read_text().splitlines():
  m=re.match(r'; ===== \S+ @ ([0-9a-f]+) =====',line)
  if m:cur=int(m.group(1),16);funcs[cur]=[];continue
  m=re.match(r'([0-9a-f]{8})  (\S+)(?: (.*?))?  ; len (\d+)$',line)
  if m and cur is not None:funcs[cur].append((int(m.group(1),16),m.group(2),m.group(3) or '',int(m.group(4))))

SIZE={'b':1,'w':2,'l':4}
def num(s):return int(s,0)
def split_ops(s):
  parts,depth,buf=[],0,''
  for ch in s:
    if ch=='(':depth+=1
    if ch==')':depth-=1
    if ch==',' and depth==0:parts.append(buf);buf=''
    else:buf+=ch
  return parts+[buf] if buf else parts

class Operand:
  def __init__(self,text):
    self.text=text
    if m:=re.fullmatch(r'#(-?0x[0-9a-f]+|-?\d+)',text):self.kind,self.value='imm',num(m.group(1))
    elif m:=re.fullmatch(r'\((0x[0-9a-f]+)\)\.l',text):self.kind,self.value='abs',num(m.group(1))
    elif m:=re.fullmatch(r'\(A([0-7])\)',text):self.kind,self.reg,self.disp='ind',int(m.group(1)),0
    elif m:=re.fullmatch(r'\((-?0x[0-9a-f]+),A([0-7])\)',text):self.kind,self.reg,self.disp='ind',int(m.group(2)),num(m.group(1))
    elif m:=re.fullmatch(r'D([0-7])[bwl]?',text):self.kind,self.reg='d',int(m.group(1))
    elif m:=re.fullmatch(r'A([0-7])',text):self.kind,self.reg='a',int(m.group(1))
    elif m:=re.fullmatch(r'0x([0-9a-f]+)(?:\.l)?',text):self.kind,self.value='target',int(m.group(1),16)
    else:raise ValueError(f'unsupported operand {text}')
  def addr(self):
    if self.kind=='abs':return f'0x{self.value&0xffffff:x}'
    if self.kind=='ind':return f'(c.a[{self.reg}]+{self.disp})' if self.disp else f'c.a[{self.reg}]'
    raise ValueError(self.text)
  def read(self,size):
    if self.kind=='imm':return f'0x{self.value&((1<<(8*size))-1):x}'
    if self.kind=='d':return f'c.d[{self.reg}]'
    if self.kind=='a':return f'c.a[{self.reg}]'
    return f'm.r({size},{self.addr()})'
  def write(self,size,value):
    if self.kind=='d':return f'c.set({self.reg},{size},{value})'
    if self.kind in('abs','ind'):return f'm.w({size},{self.addr()},{value})'
    raise ValueError(self.text)

COND={'bne':'!c.z','beq':'c.z','bhi':'!c.c&&!c.z','bls':'c.c||c.z','bra':'true'}
def translate(addr,mn,ops):
  base,_,suffix=mn.partition('.');size=SIZE.get(suffix,4);o=[Operand(x) for x in split_ops(ops)] if ops else []
  if base in COND:return f'if({COND[base]}){{pc=0x{o[0].value:x};continue;}}'
  if base=='rts':return 'return;'
  if base=='jsr':
    if o[0].value!=EVENT:raise ValueError(f'unexpected call {ops} at {addr:x}')
    return 'm.event(c.d[2]&0xff);'
  if base=='dbf':return f'if(c.dbf({o[0].reg})){{pc=0x{o[1].value:x};continue;}}'
  if base in('cmpi','cmp'):return f'c.cmp({size},{o[1].read(size)},{o[0].read(size)});'
  if base=='tst':return f'c.tst({size},{o[0].read(size)});'
  if base=='btst':
    bits=8 if o[1].kind!='d' else 32
    return f'c.btst({o[0].read(4)}%{bits},{o[1].read(size)});'
  if base in('bset','bclr'):
    bits=8 if o[1].kind!='d' else 32;op='|' if base=='bset' else '&~'
    v=o[1].read(size);return f'c.btst({o[0].read(4)}%{bits},{v});'+o[1].write(size,f'{v}{op}(1<<({o[0].read(4)}%{bits}))')
  if base=='move':return f'c.tst({size},{o[0].read(size)});'+o[1].write(size,o[0].read(size))
  if base=='lea':return f'c.a[{o[1].reg}]={o[0].addr()};'
  if base=='adda':return f'c.a[{o[1].reg}]=(c.a[{o[1].reg}]+{o[0].read(size)})>>>0;'
  if base in('addq','add'):return o[1].write(size,f'c.add({size},{o[1].read(size)},{o[0].read(size)})')
  if base=='subq':return o[1].write(size,f'c.sub({size},{o[1].read(size)},{o[0].read(size)})')
  if base=='andi':return f'c.tst({size},{o[1].read(size)}&{o[0].read(size)});'+o[1].write(size,f'{o[1].read(size)}&{o[0].read(size)}')
  if base=='clr':return f'c.tst({size},0);'+o[0].write(size,'0')
  if base=='divu':return f'c.divu({o[1].reg},{o[0].read(2)});'
  if base=='swap':return f'c.swap({o[0].reg});'
  raise ValueError(f'unsupported instruction {mn} {ops} at {addr:x}')

# Handlers share tails (e.g. stage 10 branches into stage 6's rts), so follow control flow across function bodies.
code={a:(a,mn,ops) for f in funcs.values() for a,mn,ops,n in f}
succ={a:a+n for f in funcs.values() for a,mn,ops,n in f}
covered=sorted((a,a+n) for a,n in {(a,n) for f in funcs.values() for a,_,_,n in f})
for (a,e),(b,_) in zip(covered,covered[1:]):
  if e>b:raise ValueError(f'overlapping instructions at 0x{a:x}/0x{b:x}')
def branch_target(mn,ops):
  return int(split_ops(ops)[-1],16) if mn.split('.')[0] in COND or mn.startswith('dbf') else None
handlers=[]
for stage,entry in enumerate(entries):
  reach,todo,targets=set(),[entry],{entry}
  while todo:
    a=todo.pop()
    if a in reach:continue
    if a not in code:raise ValueError(f'stage {stage} reaches undecoded 0x{a:x}')
    reach.add(a);_,mn,ops=code[a];t=branch_target(mn,ops)
    if t is not None:targets.add(t);todo.append(t)
    if mn not in('rts','bra.w'):todo.append(succ[a])
  body=[];prev=None
  for a in sorted(reach):
    _,mn,ops=code[a]
    if prev is not None and succ[prev]!=a and code[prev][1] not in('rts','bra.w'):body.append(f'  pc=0x{succ[prev]:x};continue;');targets.add(succ[prev])
    prev=a
  prev=None
  for a in sorted(reach):
    _,mn,ops=code[a]
    if prev is not None and succ[prev]!=a and code[prev][1] not in('rts','bra.w'):body.append(f'  pc=0x{succ[prev]:x};continue;')
    if a in targets:body.append(f'case 0x{a:x}:')
    body.append(f'  {translate(a,mn,ops)} // {mn} {ops}');prev=a
  handlers.append(f'// Stage {stage}: ROM 0x{entry:x}\n(m,c)=>{{let pc=0x{entry:x};for(;;)switch(pc){{\n'+'\n'.join(body)+'\n  default:throw Error(`stage '+str(stage)+' jump 0x${pc.toString(16)}`);}}')

digest=hashlib.sha256(listing.read_bytes()).hexdigest()[:16]
out.write_text(f'''// Generated by tools/export_stage_rules.py from md-game-analysis/logic/stage_events/listing.asm (sha256 {digest}). Do not edit.
// 36 battle-stage condition handlers from ROM table 0x120E8, one statement per original 68000 instruction.
// m.r(size,address)/m.w(size,address,value) access battle state; m.event(id) is the original 0x14144 event start.
export class StageCpu {{
  constructor(){{this.d=new Array(8).fill(0);this.a=new Array(8).fill(0);this.z=false;this.n=false;this.c=false;this.v=false;}}
  static mask(size){{return size===4?0xffffffff:(1<<(size*8))-1;}}
  set(reg,size,value){{const mask=StageCpu.mask(size);this.d[reg]=size===4?value>>>0:((this.d[reg]&~mask)|(value&mask))>>>0;}}
  flags(size,result){{const mask=StageCpu.mask(size);result=(result&mask)>>>0;this.z=result===0;this.n=((result>>>(size*8-1))&1)===1;return result;}}
  cmp(size,dst,src){{const mask=StageCpu.mask(size);dst=(dst&mask)>>>0;src=(src&mask)>>>0;const r=this.flags(size,dst-src);this.c=src>dst;this.v=((((dst^src)&(dst^r))>>>(size*8-1))&1)===1;}}
  tst(size,value){{this.flags(size,value);this.c=false;this.v=false;}}
  btst(bit,value){{this.z=((value>>>bit)&1)===0;}}
  add(size,dst,src){{const mask=StageCpu.mask(size);dst=(dst&mask)>>>0;src=(src&mask)>>>0;const r=this.flags(size,dst+src);this.c=dst+src>mask;this.v=((((~(dst^src))&(dst^r))>>>(size*8-1))&1)===1;return r;}}
  sub(size,dst,src){{this.cmp(size,dst,src);return (dst-src)&StageCpu.mask(size);}}
  dbf(reg){{const w=((this.d[reg]&0xffff)-1)&0xffff;this.set(reg,2,w);return w!==0xffff;}}
  divu(reg,divisor){{const value=this.d[reg]>>>0,q=Math.floor(value/divisor);if(q>0xffff){{this.v=true;return;}}this.d[reg]=(((value%divisor)<<16)|q)>>>0;this.flags(2,q);this.c=false;this.v=false;}}
  swap(reg){{const v=this.d[reg]>>>0;this.d[reg]=((v<<16)|(v>>>16))>>>0;this.flags(4,this.d[reg]);this.c=false;this.v=false;}}
}}
export const STAGE_HANDLER_ADDRESSES=[{','.join(f'0x{e:x}' for e in entries)}];
export const stageHandlers=[
{(','+chr(10)).join(handlers)}
];
''')
print(json.dumps({'stages':len(handlers),'instructions':sum(len(funcs[e]) for e in entries),'distinctInstructions':len(code),'output':str(out.relative_to(root))}))
