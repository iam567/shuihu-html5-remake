/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00019cf6 */

void FUN_00019cf6(void)

{
  uint unaff_D4;
  
  Seed_1060();
  if ((short)((unaff_D4 & 0xffff) / 10) == 0) {
    Seed_1060();
  }
  else {
    Seed_1060();
  }
  return;
}

