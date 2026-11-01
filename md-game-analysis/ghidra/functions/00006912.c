/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006912 */

void FUN_00006912(void)

{
  short sVar1;
  undefined4 *puVar2;
  
  sVar1 = 0x3ff;
  puVar2 = &DAT_00ffb000;
  do {
    *puVar2 = 0xffffffff;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (sVar1 != -1);
  return;
}

