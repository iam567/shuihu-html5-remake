/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000125f8 */

void FUN_000125f8(void)

{
  short sVar1;
  undefined4 *puVar2;
  
  if (DAT_00ffe780._0_1_ == '\0') {
    if (DAT_00ff6310 == '\0') {
      FUN_00014144();
    }
  }
  else if (DAT_00ffe1f5 == 0xff) {
    if ((DAT_00ff6019 & 2) == 0) {
      DAT_00ffe1d0 = 0;
      DAT_00ffe1f5 = 0;
      FUN_00014144();
    }
  }
  else {
    if (DAT_00ff6085 == '\0') {
      puVar2 = &DAT_00ffe780;
      sVar1 = 4;
      do {
        if (*(int *)((int)puVar2 + 2) == 0x1400040) {
          if (DAT_00ff6310 != '\0') {
            return;
          }
          if ((DAT_00ff614f & 1) != 0) {
            return;
          }
          FUN_00014144();
          return;
        }
        puVar2 = puVar2 + 0x10;
        sVar1 = sVar1 + -1;
      } while (sVar1 != -1);
    }
    if ((((DAT_00ffe1f7 == '\x02') && (DAT_00ff6102 == '\x01')) && (DAT_00ffe1d0 <= DAT_00ffe1f5))
       && ((DAT_00ffe1d0 = DAT_00ffe1d0 + 1, DAT_00ffe1f5 != 0 && (DAT_00ffe1f5 < 8)))) {
      FUN_00014144();
    }
  }
  return;
}

