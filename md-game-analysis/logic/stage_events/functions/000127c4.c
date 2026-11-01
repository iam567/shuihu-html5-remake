/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000127c4 */

void FUN_000127c4(void)

{
  short sVar1;
  char *pcVar2;
  
  if (DAT_00ffe780._0_1_ != '\0') {
    pcVar2 = &DAT_00ffe7c0;
    sVar1 = 10;
    do {
      if (*pcVar2 == '\x11') {
        if (DAT_00ffe1f5 != -1) {
          pcVar2 = &DAT_00ffea80;
          sVar1 = 0x11;
          do {
            if (*pcVar2 != '\0') {
              return;
            }
            pcVar2 = pcVar2 + 0x40;
            sVar1 = sVar1 + -1;
          } while (sVar1 != -1);
          if ((DAT_00ff6310 == '\0') && ((DAT_00ff614f & 1) == 0)) {
            FUN_00014144();
          }
          return;
        }
        if ((DAT_00ff6019 & 2) != 0) {
          return;
        }
        DAT_00ffe1f5 = 0;
        FUN_00014144();
        return;
      }
      pcVar2 = pcVar2 + 0x40;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
  }
  if (DAT_00ff6310 != '\0') {
    return;
  }
  FUN_00014144();
  return;
}

