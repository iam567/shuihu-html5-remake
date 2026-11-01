/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00013aea */

void FUN_00013aea(void)

{
  short sVar1;
  byte bVar2;
  char *pcVar3;
  
  if (DAT_00ffe780._0_1_ == '\0') {
    if (DAT_00ff6310 == '\0') {
      FUN_00014144();
    }
  }
  else if (DAT_00ffe1f5 == -1) {
    if ((DAT_00ff6019 & 2) == 0) {
      DAT_00ffe1fc = DAT_00ffe1fc & 0xffffdfff;
      DAT_00ffe1f5 = '\0';
      FUN_00014144();
    }
  }
  else if (DAT_00ffea80 == '\0') {
    if ((DAT_00ff6310 == '\0') && ((DAT_00ff614f & 1) == 0)) {
      FUN_00014144();
    }
  }
  else if ((((DAT_00ffe1fc & 0x2000) == 0) && (DAT_00ffe1f7 == '\x02')) && (DAT_00ff6102 == '\x01'))
  {
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
    if (bVar2 < 7) {
      DAT_00ffe1fc = DAT_00ffe1fc | 0x2000;
      FUN_00014144();
    }
  }
  return;
}

