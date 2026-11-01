/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000aafe */

void FUN_0000aafe(void)

{
  if ((DAT_00ff6004 & 0xf0) == 0) {
    if ((DAT_00ff6003 & 4) == 0) {
      if ((DAT_00ff6003 & 8) == 0) {
        if ((DAT_00ff6003 & 1) == 0) {
          if (((DAT_00ff6003 & 2) != 0) && ((short)DAT_00ff604a < 0x160)) {
            if ((0xdf < (short)DAT_00ff604a) && ((char)(DAT_00ffe107 + -7) != DAT_00ffe105)) {
              DAT_00ffe105 = DAT_00ffe105 + '\x01';
              DAT_00ff615c = DAT_00ff615c | 2;
              FUN_000032f2();
              DAT_00ff6038 = 1;
              DAT_00ff6039 = 0x20;
            }
            DAT_00ff604c = 0x20;
            DAT_00ff604d = 1;
          }
        }
        else if (0x80 < DAT_00ff604a) {
          if ((DAT_00ff604a < 0xe1) && (DAT_00ffe105 != '\0')) {
            DAT_00ffe105 = DAT_00ffe105 + -1;
            DAT_00ff615c = DAT_00ff615c | 1;
            FUN_000032c4();
            DAT_00ff6038 = 0;
            DAT_00ff6039 = 0x20;
          }
          DAT_00ff604c = 0x20;
          DAT_00ff604d = 0;
        }
      }
      else if ((short)DAT_00ff6048 < 0x1a0) {
        if ((0x11f < (short)DAT_00ff6048) && ((char)(DAT_00ffe106 + -10) != DAT_00ffe104)) {
          DAT_00ffe104 = DAT_00ffe104 + '\x01';
          DAT_00ff615c = DAT_00ff615c | 8;
          FUN_00003354();
          DAT_00ff6038 = 3;
          DAT_00ff6039 = 0x20;
        }
        DAT_00ff604c = 0x20;
        DAT_00ff604d = 3;
      }
    }
    else if (0x80 < DAT_00ff6048) {
      if ((DAT_00ff6048 < 0x101) && (DAT_00ffe104 != '\0')) {
        DAT_00ffe104 = DAT_00ffe104 + -1;
        DAT_00ff615c = DAT_00ff615c | 4;
        FUN_00003326();
        DAT_00ff6038 = 2;
        DAT_00ff6039 = 0x20;
      }
      DAT_00ff604c = 0x20;
      DAT_00ff604d = 2;
    }
  }
  else {
    FUN_00006912();
    FUN_00006928();
    FUN_00001098();
    FUN_00007c14();
    DAT_00ff606b = DAT_00ff605b;
    DAT_00ff6085 = 0;
  }
  return;
}

