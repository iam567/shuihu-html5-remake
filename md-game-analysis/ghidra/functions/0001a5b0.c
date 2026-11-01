/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001a5b0 */

void FUN_0001a5b0(void)

{
  if (((DAT_00ff6181 & 1) != 0) && ((DAT_00ff6004 & 0x40) != 0)) {
    DAT_00ff6181 = 0;
    DAT_00ff6124 = 0;
    FUN_0000f772();
    DAT_00ff603d = DAT_00ff603d | 2;
  }
  return;
}

