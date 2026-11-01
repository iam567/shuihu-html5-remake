/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006588 */

void FUN_00006588(void)

{
  if ((DAT_00ff605a != '\0') && (DAT_00ff604c == '\0')) {
    FUN_00006744();
    FUN_00006772();
    if (DAT_00ff6058 == DAT_00ff6054) {
      if (DAT_00ff6056 == DAT_00ff6052) {
        DAT_00ff604c = '\0';
        DAT_00ff605a = '\0';
        DAT_00ff6036 = 1;
        DAT_00ffe10e = DAT_00ffe1f6;
        DAT_00ff603d = DAT_00ff603d | 2;
      }
      else if (DAT_00ff6052 < DAT_00ff6056) {
        if ((DAT_00ff6048 < 0x101) && (DAT_00ffe104 != '\0')) {
          DAT_00ffe104 = DAT_00ffe104 + -1;
          DAT_00ff615c = DAT_00ff615c | 4;
          FUN_00003326();
          DAT_00ff6038 = 2;
          DAT_00ff6039 = 0x20;
        }
        DAT_00ff604d = 2;
        DAT_00ff604c = ' ';
      }
      else {
        if ((0x11f < (short)DAT_00ff6048) && ((char)(DAT_00ffe106 + -10) != DAT_00ffe104)) {
          DAT_00ffe104 = DAT_00ffe104 + '\x01';
          DAT_00ff615c = DAT_00ff615c | 8;
          FUN_00003354();
          DAT_00ff6038 = 3;
          DAT_00ff6039 = 0x20;
        }
        DAT_00ff604d = 3;
        DAT_00ff604c = ' ';
      }
    }
    else if (DAT_00ff6054 < DAT_00ff6058) {
      if ((DAT_00ff604a < 0xe1) && (DAT_00ffe105 != '\0')) {
        DAT_00ffe105 = DAT_00ffe105 + -1;
        DAT_00ff615c = DAT_00ff615c | 1;
        FUN_000032c4();
        DAT_00ff6038 = 0;
        DAT_00ff6039 = 0x20;
      }
      DAT_00ff604d = 0;
      DAT_00ff604c = ' ';
    }
    else {
      if ((0xdf < (short)DAT_00ff604a) && ((char)(DAT_00ffe107 + -7) != DAT_00ffe105)) {
        DAT_00ffe105 = DAT_00ffe105 + '\x01';
        DAT_00ff615c = DAT_00ff615c | 2;
        FUN_000032f2();
        DAT_00ff6038 = 1;
        DAT_00ff6039 = 0x20;
      }
      DAT_00ff604d = 1;
      DAT_00ff604c = ' ';
    }
  }
  return;
}

