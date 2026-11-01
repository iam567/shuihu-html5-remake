import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.io.*;
import java.util.*;
// Battle-stage scheduler export: jump table 0x120E8 (36 longs) used by 0x12074, plus every callee.
public class ExportStageHandlers extends GhidraScript {
 public void run() throws Exception {
  Path out=Paths.get(getScriptArgs()[0]);Files.createDirectories(out.resolve("functions"));
  Deque<Address> todo=new ArrayDeque<>();Set<Address> seen=new TreeSet<>();
  todo.add(toAddr(0x12074));
  for(int i=0;i<36;i++)todo.add(toAddr(getInt(toAddr(0x120e8+i*4))&0xffffffffL));
  // The saved project left some handler bytes as undefined data (e.g. 0x13438 in stage 23); re-disassemble the
  // whole scheduler range by flow from every entry before exporting.
  clearListing(toAddr(0x12074),toAddr(0x14183));
  for(Address e:todo)new DisassembleCommand(e,null,true).applyTo(currentProgram,monitor);
  DecompInterface dec=new DecompInterface();dec.openProgram(currentProgram);
  try(PrintWriter idx=new PrintWriter(Files.newBufferedWriter(out.resolve("functions.tsv")));PrintWriter asm=new PrintWriter(Files.newBufferedWriter(out.resolve("listing.asm")))){
   idx.println("address\tname\tbody_bytes\tdecompiled\tcallees");
   while(!todo.isEmpty()&&!monitor.isCancelled()){
    Address a=todo.poll();if(!seen.add(a)||a.getOffset()>=0x200000)continue;
    if(getInstructionAt(a)==null)new DisassembleCommand(a,null,true).applyTo(currentProgram,monitor);
    Function f=getFunctionAt(a);if(f!=null)removeFunction(f);f=createFunction(a,null);
    if(f==null){idx.println(a+"\t?\t0\tfalse\t");continue;}
    List<String> callees=new ArrayList<>();
    asm.println("\n; ===== "+f.getName()+" @ "+a+" =====");
    InstructionIterator ins=currentProgram.getListing().getInstructions(f.getBody(),true);
    while(ins.hasNext()){Instruction i=ins.next();asm.println(i.getAddress()+"  "+i+"  ; len "+i.getLength());
     for(Reference r:i.getReferencesFrom())if(r.getReferenceType().isCall()){callees.add(r.getToAddress().toString());todo.add(r.getToAddress());}}
    DecompileResults r=dec.decompileFunction(f,60,monitor);
    String code=r.decompileCompleted()?r.getDecompiledFunction().getC():"/* Decompile failed: "+r.getErrorMessage()+" */";
    Files.writeString(out.resolve("functions/"+a+".c"),"/* Ghidra 12.1.4 pseudocode, not original source. ROM address "+a+" */\n"+code);
    idx.println(a+"\t"+f.getName()+"\t"+f.getBody().getNumAddresses()+"\t"+r.decompileCompleted()+"\t"+String.join(",",callees));
   }
  }finally{dec.dispose();}
  println("STAGE export "+seen.size()+" addresses");
 }
}
