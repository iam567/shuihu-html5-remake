/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00012224 */

void FUN_00012224(void)

{
  short sVar1;
  byte bVar2;
  undefined4 *puVar3;
  char *pcVar4;
  
  if (DAT_00ffe780._0_1_ == '\0') {
    if (DAT_00ff6310 == '\0') {
      FUN_00014144();
    }
  }
  else if (DAT_00ffe1f5 == 0xff) {
    if ((DAT_00ff6019 & 2) == 0) {
      DAT_00ffe1f5 = 0;
      DAT_00ffe1d0 = 0;
      FUN_00014144();
    }
  }
  else {
    if (DAT_00ff6085 == '\0') {
      puVar3 = &DAT_00ffe780;
      sVar1 = 4;
      do {
        if (*(int *)((int)puVar3 + 2) == 0x1600020) {
          if (DAT_00ff6310 != '\0') {
            return;
          }
          if ((DAT_00ff614f & 1) != 0) {
            return;
          }
          FUN_00014144();
          return;
        }
        puVar3 = puVar3 + 0x10;
        sVar1 = sVar1 + -1;
      } while (sVar1 != -1);
    }
    if ((((DAT_00ffe1f7 == '\x02') && (DAT_00ff6102 == '\x01')) && (DAT_00ffe1d0 <= DAT_00ffe1f5))
       && (DAT_00ffe1d0 = DAT_00ffe1d0 + 1, DAT_00ffe1f5 != 0)) {
      bVar2 = 0;
      pcVar4 = &DAT_00ffea80;
      sVar1 = 0x11;
      do {
        if (*pcVar4 != '\0') {
          bVar2 = bVar2 + 1;
        }
        pcVar4 = pcVar4 + 0x40;
        sVar1 = sVar1 + -1;
      } while (sVar1 != -1);
      if (bVar2 < 7) {
        FUN_00014144();
      }
    }
  }
  return;
}

