/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001b62e */

short FUN_0001b62e(void)

{
  short sVar1;
  char cVar2;
  short sVar3;
  
  sVar1 = 0x440;
  sVar3 = 6;
  cVar2 = DAT_00ff617f;
  do {
    if (DAT_00ff618a <= cVar2) break;
    sVar1 = FUN_0000b7fe();
    cVar2 = cVar2 + '\x01';
    sVar1 = sVar1 + 0x10;
    sVar3 = sVar3 + -1;
  } while (sVar3 != -1);
  sVar3 = 6;
  cVar2 = DAT_00ff617f;
  do {
    if (DAT_00ff618a <= cVar2) {
      return sVar1;
    }
    sVar1 = FUN_0001add8();
    cVar2 = cVar2 + '\x01';
    sVar3 = sVar3 + -1;
  } while (sVar3 != -1);
  return sVar1;
}

