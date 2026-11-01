import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import java.nio.file.*;
import java.io.*;
// Usage: -postScript ExportFunctionsAt.java <outdir> <hexaddr>... ; writes <addr>.c and <addr>.asm for each entry.
public class ExportFunctionsAt extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs();Path out=Paths.get(args[0]);Files.createDirectories(out);
  DecompInterface dec=new DecompInterface();dec.openProgram(currentProgram);
  try{
   for(int k=1;k<args.length;k++){
    Address a=toAddr(Long.parseLong(args[k],16));
    if(getInstructionAt(a)==null){clearListing(a,a.add(1));new DisassembleCommand(a,null,true).applyTo(currentProgram,monitor);}
    Function f=getFunctionAt(a);if(f==null)f=createFunction(a,null);
    try(PrintWriter asm=new PrintWriter(Files.newBufferedWriter(out.resolve(a+".asm")))){
     InstructionIterator ins=currentProgram.getListing().getInstructions(f.getBody(),true);
     while(ins.hasNext()){Instruction i=ins.next();asm.println(i.getAddress()+"  "+i+"  ; len "+i.getLength());}
    }
    DecompileResults r=dec.decompileFunction(f,60,monitor);
    Files.writeString(out.resolve(a+".c"),"/* Ghidra 12.1.4 pseudocode, not original source. ROM address "+a+" */\n"+(r.decompileCompleted()?r.getDecompiledFunction().getC():"/* failed */"));
   }
  }finally{dec.dispose();}
 }
}
