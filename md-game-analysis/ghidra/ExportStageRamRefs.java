import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.io.*;
// Every code reference to the RAM bytes the stage scheduler reads, with the instruction and containing function.
public class ExportStageRamRefs extends GhidraScript {
 public void run() throws Exception {
  Path out=Paths.get(getScriptArgs()[0]);
  long[] ram={0xffe1f5,0xffe1fc,0xffe1fd,0xffe1fe,0xffe1ff,0xff6310,0xff6019,0xff614f,0xffe1f7,0xff6102,0xffe1d0,0xff609a,0xff6085,0xffe10e,0xffe10f,0xffe1f4,0xffe1e0,0xffe1f6,0xff603d,0xff6036};
  try(PrintWriter w=new PrintWriter(Files.newBufferedWriter(out.resolve("ram-refs.tsv")))){
   w.println("ram\tfrom\ttype\tfunction\tinstruction");
   ReferenceManager rm=currentProgram.getReferenceManager();
   for(long v:ram){
    Address a=toAddr(v);
    for(Reference r:rm.getReferencesTo(a)){
     Address f=r.getFromAddress();Function fn=getFunctionContaining(f);Instruction i=getInstructionAt(f);
     w.println(Long.toHexString(v)+"\t"+f+"\t"+r.getReferenceType()+"\t"+(fn==null?"-":fn.getEntryPoint()+" "+fn.getName())+"\t"+(i==null?"":i.toString()));
    }
   }
  }
 }
}
