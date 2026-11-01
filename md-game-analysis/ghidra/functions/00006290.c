/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006290 */

void FUN_00006290(void)

{
  if ((DAT_00ff604e != '\0') && (DAT_00ff6030 == '\0')) {
    FUN_00003218();
    FUN_000031ea();
    if (DAT_00ff6026 == DAT_00ff6054) {
      if (DAT_00ff6024 == DAT_00ff6052) {
        DAT_00ff604e = '\0';
        DAT_00ff603d = DAT_00ff603d | 2;
      }
      else if (DAT_00ff6052 < DAT_00ff6024) {
        if (DAT_00ff6020 < 0x101) {
          DAT_00ffe104 = DAT_00ffe104 + -1;
          DAT_00ff618f = DAT_00ff618f | 4;
          FUN_00003326();
          DAT_00ff6038 = 2;
          DAT_00ff6039 = 0x20;
        }
        DAT_00ffe006 = 2;
        DAT_00ff6030 = ' ';
      }
      else {
        if (0x11f < (short)DAT_00ff6020) {
          DAT_00ffe104 = DAT_00ffe104 + '\x01';
          DAT_00ff618f = DAT_00ff618f | 8;
          FUN_00003354();
          DAT_00ff6038 = 3;
          DAT_00ff6039 = 0x20;
        }
        DAT_00ffe006 = 3;
        DAT_00ff6030 = ' ';
      }
    }
    else if (DAT_00ff6054 < DAT_00ff6026) {
      if (DAT_00ff6022 < 0xe1) {
        DAT_00ffe105 = DAT_00ffe105 + -1;
        DAT_00ff618f = DAT_00ff618f | 1;
        FUN_000032c4();
        DAT_00ff6038 = 0;
        DAT_00ff6039 = 0x20;
      }
      DAT_00ffe006 = 0;
      DAT_00ff6030 = ' ';
    }
    else {
      if (0xdf < (short)DAT_00ff6022) {
        DAT_00ffe105 = DAT_00ffe105 + '\x01';
        DAT_00ff618f = DAT_00ff618f | 2;
        FUN_000032f2();
        DAT_00ff6038 = 1;
        DAT_00ff6039 = 0x20;
      }
      DAT_00ffe006 = 1;
      DAT_00ff6030 = ' ';
    }
  }
  return;
}

