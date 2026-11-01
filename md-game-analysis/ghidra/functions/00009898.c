/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009898 */

void FUN_00009898(void)

{
  short sVar1;
  undefined4 *puVar2;
  
  sVar1 = 0x3ff;
  puVar2 = (undefined4 *)&DAT_00ff5000;
  do {
    *puVar2 = 0;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (sVar1 != -1);
  return;
}

