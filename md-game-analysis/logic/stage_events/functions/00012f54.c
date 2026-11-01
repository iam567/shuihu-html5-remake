/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00012f54 */

void FUN_00012f54(void)

{
  short sVar1;
  char *pcVar2;
  
  if (((DAT_00ffe780._0_1_ == '\0') || (DAT_00ffea00 == '\0')) || (DAT_00ffea40 == '\0')) {
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
  else {
    pcVar2 = &DAT_00ffea80;
    sVar1 = 0x11;
    do {
      if (*pcVar2 != '\0') {
        if ((DAT_00ffe1fc & 0x20) != 0) {
          return;
        }
        if (DAT_00ffea92 != 0) {
          return;
        }
        if (DAT_00ff609a != '\0') {
          return;
        }
        DAT_00ff6019 = DAT_00ff6019 & 0xfb;
        DAT_00ffe1fc = DAT_00ffe1fc | 0x20;
        FUN_00014144();
        return;
      }
      pcVar2 = pcVar2 + 0x40;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    if ((DAT_00ff6310 == '\0') && ((DAT_00ff614f & 1) == 0)) {
      FUN_00014144();
    }
  }
  return;
}

