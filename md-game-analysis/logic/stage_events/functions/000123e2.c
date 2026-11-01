/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000123e2 */

void FUN_000123e2(void)

{
  if (DAT_00ffe780._0_1_ == '\0') {
    if (DAT_00ff6310 == '\0') {
      FUN_00014144();
    }
  }
  else if (DAT_00ffe1f5 == -1) {
    if ((DAT_00ff6019 & 2) == 0) {
      DAT_00ffe1f5 = '\0';
      FUN_00014144();
    }
  }
  else if (((DAT_00ffea80 == '\0') && (DAT_00ff6310 == '\0')) && ((DAT_00ff614f & 1) == 0)) {
    FUN_00014144();
  }
  return;
}

