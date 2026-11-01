/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000135ea */

void FUN_000135ea(void)

{
  short sVar1;
  byte bVar2;
  char *pcVar3;
  undefined4 *puVar4;
  
  if (DAT_00ffe780._0_1_ == '\0') {
    if (DAT_00ff6310 == '\0') {
      FUN_00014144();
    }
  }
  else if (DAT_00ffe1f5 == -1) {
    if ((DAT_00ff6019 & 2) == 0) {
      DAT_00ffe1fc = DAT_00ffe1fc & 0xfffffdff;
      DAT_00ffe1f5 = '\0';
      FUN_00014144();
    }
  }
  else {
    pcVar3 = &DAT_00ffea80;
    sVar1 = 0x11;
    do {
      if (*pcVar3 != '\0') {
        if ((DAT_00ffe1fc & 0x200) != 0) {
          return;
        }
        if (DAT_00ffe1f7 != '\x02') {
          return;
        }
        if (DAT_00ff6102 != '\x01') {
          return;
        }
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
        if (6 < bVar2) {
          return;
        }
        puVar4 = &DAT_00ffe780;
        sVar1 = 0xb;
        do {
          if (*(ushort *)((int)puVar4 + 2) < 0x181) {
            DAT_00ffe1fc = DAT_00ffe1fc | 0x200;
            FUN_00014144();
            return;
          }
          puVar4 = puVar4 + 0x10;
          sVar1 = sVar1 + -1;
        } while (sVar1 != -1);
        return;
      }
      pcVar3 = pcVar3 + 0x40;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    if ((DAT_00ff6310 == '\0') && ((DAT_00ff614f & 1) == 0)) {
      FUN_00014144();
    }
  }
  return;
}

