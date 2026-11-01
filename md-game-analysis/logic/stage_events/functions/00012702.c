/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00012702 */

void FUN_00012702(void)

{
  short sVar1;
  char cVar2;
  char *pcVar3;
  
  if (DAT_00ffe780._0_1_ != '\0') {
    cVar2 = '\0';
    pcVar3 = (char *)&DAT_00ffe780;
    sVar1 = 0xb;
    do {
      if (*pcVar3 == '\x04') {
        cVar2 = cVar2 + '\x01';
      }
      if (*pcVar3 == '\x11') {
        cVar2 = cVar2 + '\x01';
      }
      pcVar3 = pcVar3 + 0x40;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    if (cVar2 == '\x02') {
      if (DAT_00ffe1f5 == -1) {
        if ((DAT_00ff6019 & 2) != 0) {
          return;
        }
        DAT_00ffe1f5 = 0;
        FUN_00014144();
        return;
      }
      pcVar3 = &DAT_00ffea80;
      sVar1 = 0x11;
      do {
        if (*pcVar3 != '\0') {
          return;
        }
        pcVar3 = pcVar3 + 0x40;
        sVar1 = sVar1 + -1;
      } while (sVar1 != -1);
      if (DAT_00ff6310 != '\0') {
        return;
      }
      if ((DAT_00ff614f & 1) != 0) {
        return;
      }
      FUN_00014144();
      return;
    }
  }
  if (DAT_00ff6310 == '\0') {
    FUN_00014144();
  }
  return;
}

