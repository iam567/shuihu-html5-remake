/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001762e */

void FUN_0001762e(void)

{
  uint unaff_D4;
  uint uVar1;
  
  uVar1 = unaff_D4 & 0xffff;
  do {
    uVar1 = uVar1 / 10;
    Seed_1028();
  } while ((short)uVar1 != 0);
  return;
}

