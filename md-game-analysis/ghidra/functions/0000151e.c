/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000151e */

void FUN_0000151e(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  sVar1 = 0x1df;
  puVar2 = &DAT_00001536;
  puVar3 = &DAT_00ffe780;
  do {
    *puVar3 = *puVar2;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  } while (sVar1 != -1);
  return;
}

