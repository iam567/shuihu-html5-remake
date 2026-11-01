import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.mem.MemoryBlock;
public class PrepareMegaDrive extends GhidraScript {
 public void run() throws Exception {
  MemoryBlock rom=currentProgram.getMemory().getBlock(toAddr(0)); rom.setName("ROM");rom.setWrite(false);rom.setExecute(true);
  MemoryBlock ram=currentProgram.getMemory().createUninitializedBlock("RAM",toAddr(0xff0000),0x10000,false);ram.setRead(true);ram.setWrite(true);
  MemoryBlock mir=currentProgram.getMemory().createUninitializedBlock("RAM_SIGN_EXTENDED",toAddr(0xffff0000L),0x10000,false);mir.setRead(true);mir.setWrite(true);
  MemoryBlock io=currentProgram.getMemory().createUninitializedBlock("IO",toAddr(0xa00000),0x20000,false);io.setRead(true);io.setWrite(true);io.setVolatile(true);
  MemoryBlock vdp=currentProgram.getMemory().createUninitializedBlock("VDP",toAddr(0xc00000),0x20,false);vdp.setRead(true);vdp.setWrite(true);vdp.setVolatile(true);
  for(int off=4;off<0x100;off+=4){long v=Integer.toUnsignedLong(getInt(toAddr(off)));if(v<0x200000 && v!=0){Address a=toAddr(v);addEntryPoint(a);disassemble(a);if(getFunctionAt(a)==null)createFunction(a,off==4?"ResetEntry":"Vector_"+Integer.toHexString(off));}}
  long[] seeds={0x7a6,0xe50,0x1028,0x1060,0x17698,0x7622,0x18274};
  for(long v:seeds){Address a=toAddr(v);disassemble(a);if(getFunctionAt(a)==null)createFunction(a,"Seed_"+Long.toHexString(v));}
  println("MEGADRIVE prepared base=0 reset=0x4ba; RAM aliases are independent modeled blocks; seed names are analyst assertions.");
 }
}
