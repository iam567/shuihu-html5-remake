import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.io.*;
public class ExportMegaDrive extends GhidraScript {
 public void run() throws Exception {
  Path out=Paths.get(getScriptArgs()[0]);Files.createDirectories(out.resolve("functions"));
  try(PrintWriter focused=new PrintWriter(Files.newBufferedWriter(out.resolve("focused-addresses.tsv")))){
   focused.println("requested_address\tcontaining_function\tname");
   for(long v:new long[]{0x4ba,0x7a6,0xe50,0x1028,0x1060,0x17698,0x7622,0x18274}){
    Function f=getFunctionContaining(toAddr(v)); focused.println(Long.toHexString(v)+"\t"+(f==null?"unknown":f.getEntryPoint()+"\t"+f.getName()));
   }
  }
  DecompInterface dec=new DecompInterface();dec.openProgram(currentProgram);
  try(PrintWriter idx=new PrintWriter(Files.newBufferedWriter(out.resolve("functions.tsv")));PrintWriter calls=new PrintWriter(Files.newBufferedWriter(out.resolve("calls.tsv")))){
   idx.println("address\tname\tbody_bytes\tdecompiled\tfile");calls.println("from\tto\ttype");
   FunctionIterator fs=currentProgram.getFunctionManager().getFunctions(true);int n=0;
   while(fs.hasNext()&&!monitor.isCancelled()){
    Function f=fs.next();String a=f.getEntryPoint().toString();String name=f.getName();DecompileResults r=dec.decompileFunction(f,30,monitor);
    String rel="functions/"+a+".c";String code=r.decompileCompleted()?r.getDecompiledFunction().getC():"/* Decompile failed: "+r.getErrorMessage()+" */";
    Files.writeString(out.resolve(rel),"/* Ghidra 12.1.4 pseudocode, not original source. ROM address "+a+" */\n"+code);
    idx.println(a+"\t"+name+"\t"+f.getBody().getNumAddresses()+"\t"+r.decompileCompleted()+"\t"+rel);
    InstructionIterator ins=currentProgram.getListing().getInstructions(f.getBody(),true);
    while(ins.hasNext()){Instruction i=ins.next();for(Reference ref:i.getReferencesFrom()){if(ref.getReferenceType().isCall())calls.println(i.getAddress()+"\t"+ref.getToAddress()+"\t"+ref.getReferenceType());}}
    if(++n%100==0)println("Exported "+n+" functions");
   }
   println("MEGADRIVE exported "+n+" functions");
  }finally{dec.dispose();}
 }
}
