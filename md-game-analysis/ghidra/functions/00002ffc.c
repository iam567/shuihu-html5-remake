/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00002ffc */

short FUN_00002ffc(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  
  sVar2 = 6;
  do {
    sVar3 = 9;
    do {
      FUN_00002e5a();
      sVar1 = FUN_00003142();
      sVar1 = sVar1 + 4;
      if (sVar1 == 0x40) {
        sVar1 = 0;
      }
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return sVar1;
}

