import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.nio.file.*;
import java.io.*;
public class InspectZ80 extends GhidraScript {
 public void run() throws Exception {
  disassemble(toAddr(0));createFunction(toAddr(0),"Reset");
  for(int i=0;i<0x5c1;i++)if(getInstructionAt(toAddr(i))==null && currentProgram.getListing().getInstructionContaining(toAddr(i))==null)disassemble(toAddr(i));
  try(PrintWriter o=new PrintWriter(Files.newBufferedWriter(Paths.get(getScriptArgs()[0])))){
   InstructionIterator it=currentProgram.getListing().getInstructions(true);while(it.hasNext()){Instruction i=it.next();o.println(i.getAddress()+"  "+i);}
  }
 }
}
