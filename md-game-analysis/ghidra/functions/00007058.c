/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007058 */

void FUN_00007058(void)

{
  uint uVar1;
  uint unaff_D4;
  
  do {
    uVar1 = unaff_D4 / 0x10;
    unaff_D4 = uVar1 & 0xffff;
    FUN_00006f50();
  } while ((short)uVar1 != 0);
  return;
}

