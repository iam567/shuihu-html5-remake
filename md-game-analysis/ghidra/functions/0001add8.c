/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001add8 */

void FUN_0001add8(void)

{
  uint uVar1;
  uint unaff_D4;
  
  do {
    uVar1 = unaff_D4 / 10;
    unaff_D4 = uVar1 & 0xffff;
    Seed_1028();
  } while ((short)uVar1 != 0);
  return;
}

