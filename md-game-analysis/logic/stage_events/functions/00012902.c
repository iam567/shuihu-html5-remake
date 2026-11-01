/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00012902 */

void FUN_00012902(void)

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
  else if ((DAT_00ffe1fc & 1) == 0) {
    if (((DAT_00ffe1f7 != '\x02') || (DAT_00ff6102 != '\x01')) || (DAT_00ffe1f5 != '\x04')) {
      return;
    }
    DAT_00ffe1fc = DAT_00ffe1fc | 1;
    FUN_00014144();
  }
  return;
}

