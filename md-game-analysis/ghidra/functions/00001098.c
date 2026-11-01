/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00001098 */

void FUN_00001098(void)

{
  short sVar1;
  
  Ram00c00004 = 0x40000003;
  sVar1 = 0xfff;
  do {
    Ram00c00000 = 0;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}

