/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e42aa */

void FUN_001e42aa(void)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = 0x250;
  puVar2 = &DAT_00ff6d04;
  do {
    *puVar2 = 0;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (sVar1 != -1);
  return;
}

