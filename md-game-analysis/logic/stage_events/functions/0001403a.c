/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001403a */

void FUN_0001403a(void)

{
  short sVar1;
  byte bVar2;
  char *pcVar3;
  
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
  else if (DAT_00ffea80 == '\0') {
    if ((DAT_00ff6310 == '\0') && ((DAT_00ff614f & 1) == 0)) {
      FUN_00014144();
    }
  }
  else if ((((DAT_00ffe1f7 == '\x02') && (DAT_00ff6102 == '\x01')) && (DAT_00ffe1d0 <= DAT_00ffe1f5)
           ) && (DAT_00ffe1d0 = DAT_00ffe1d0 + 1, DAT_00ffe1f5 != 0)) {
    bVar2 = 0;
    pcVar3 = &DAT_00ffea80;
    sVar1 = 0x11;
    do {
      if (*pcVar3 != '\0') {
        bVar2 = bVar2 + 1;
      }
      pcVar3 = pcVar3 + 0x40;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    if (bVar2 < 0x12) {
      FUN_00014144();
    }
  }
  return;
}

