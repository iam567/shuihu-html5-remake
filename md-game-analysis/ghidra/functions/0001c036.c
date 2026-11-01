/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001c036 */

void FUN_0001c036(void)

{
  char cVar1;
  short sVar2;
  
  FUN_0001b9a8();
  sVar2 = 6;
  cVar1 = DAT_00ff617f;
  do {
    if (DAT_00ff618a <= cVar1) {
      return;
    }
    FUN_0001add8();
    cVar1 = cVar1 + '\x01';
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}

