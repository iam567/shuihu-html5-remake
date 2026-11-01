/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00012c3a */

void FUN_00012c3a(void)

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
  else if (DAT_00ffea80 == '\0') {
    if ((DAT_00ff6310 == '\0') && ((DAT_00ff614f & 1) == 0)) {
      FUN_00014144();
    }
  }
  else if ((((DAT_00ffe1fc & 0x10) == 0) && (DAT_00ffec12 == 0)) && (DAT_00ff609a == '\0')) {
    DAT_00ff6019 = DAT_00ff6019 & 0xfb;
    DAT_00ffe1fc = DAT_00ffe1fc | 0x10;
    FUN_00014144();
  }
  return;
}

