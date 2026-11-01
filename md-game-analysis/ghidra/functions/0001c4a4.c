/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001c4a4 */

void FUN_0001c4a4(void)

{
  uint unaff_D5;
  
  for (; unaff_D5 != 0; unaff_D5 = unaff_D5 / 10 & 0xffff) {
    FUN_0001c524();
    DAT_00ff6190 = DAT_00ff6190 + -1;
  }
  return;
}

