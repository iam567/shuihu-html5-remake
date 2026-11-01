/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003df6 */

undefined4 FUN_00003df6(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 *puVar2;
  
  sVar1 = 0x23;
  puVar2 = &DAT_00ff7000;
  do {
    *puVar2 = 0;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (sVar1 != -1);
  return in_D0;
}

