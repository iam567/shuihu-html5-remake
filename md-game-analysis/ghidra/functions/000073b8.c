/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000073b8 */

void FUN_000073b8(void)

{
  int iVar1;
  
  if ((DAT_00ff606d != '\0') && (DAT_00ff606a == '\0')) {
    iVar1 = (int)(short)((ushort)DAT_00ff606b << 6);
    DAT_00ff6070 = *(ushort *)((int)&DAT_00ffe780 + iVar1 + 2) >> 5;
    DAT_00ff6072 = *(ushort *)((int)&DAT_00ffe784 + iVar1) >> 5;
    DAT_00ff6074 = (*(short *)((int)&DAT_00ffe780 + iVar1 + 2) - DAT_00ff6014) + 0x80;
    DAT_00ff6076 = (*(short *)((int)&DAT_00ffe784 + iVar1) - DAT_00ff6016) + 0x80;
    if (DAT_00ff6072 == DAT_00ff6054) {
      if (DAT_00ff6070 == DAT_00ff6052) {
        DAT_00ff606d = '\0';
      }
      else if (DAT_00ff6052 < DAT_00ff6070) {
        if ((DAT_00ff6074 < 0x101) && (DAT_00ffe104 != '\0')) {
          DAT_00ffe104 = DAT_00ffe104 + -1;
          DAT_00ff615c = DAT_00ff615c | 4;
          FUN_00003326();
          DAT_00ff6038 = 2;
          DAT_00ff6039 = 0x20;
        }
        *(undefined1 *)((int)&DAT_00ffe784 + iVar1 + 2) = 2;
        DAT_00ff606a = ' ';
      }
      else {
        if ((0x11f < (short)DAT_00ff6074) && ((char)(DAT_00ffe106 + -10) != DAT_00ffe104)) {
          DAT_00ffe104 = DAT_00ffe104 + '\x01';
          DAT_00ff615c = DAT_00ff615c | 8;
          FUN_00003354();
          DAT_00ff6038 = 3;
          DAT_00ff6039 = 0x20;
        }
        *(undefined1 *)((int)&DAT_00ffe784 + iVar1 + 2) = 3;
        DAT_00ff606a = ' ';
      }
    }
    else if (DAT_00ff6054 < DAT_00ff6072) {
      if ((DAT_00ff6076 < 0xe1) && (DAT_00ffe105 != '\0')) {
        DAT_00ffe105 = DAT_00ffe105 + -1;
        DAT_00ff615c = DAT_00ff615c | 1;
        FUN_000032c4();
        DAT_00ff6038 = 0;
        DAT_00ff6039 = 0x20;
      }
      *(undefined1 *)((int)&DAT_00ffe784 + iVar1 + 2) = 0;
      DAT_00ff606a = ' ';
    }
    else {
      if ((0xdf < (short)DAT_00ff6076) && ((char)(DAT_00ffe107 + -7) != DAT_00ffe105)) {
        DAT_00ffe105 = DAT_00ffe105 + '\x01';
        DAT_00ff615c = DAT_00ff615c | 2;
        FUN_000032f2();
        DAT_00ff6038 = 1;
        DAT_00ff6039 = 0x20;
      }
      *(undefined1 *)((int)&DAT_00ffe784 + iVar1 + 2) = 1;
      DAT_00ff606a = ' ';
    }
  }
  return;
}

