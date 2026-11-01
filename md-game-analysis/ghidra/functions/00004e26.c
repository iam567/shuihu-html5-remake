/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00004e26 */

void FUN_00004e26(void)

{
  int iVar1;
  uint unaff_D2;
  byte bVar2;
  int unaff_A2;
  
  if (DAT_00ff6003 == 0) {
    if (DAT_00ff60a9 == '\x01') {
      DAT_00ff60a9 = '\x02';
    }
    return;
  }
  if (DAT_00ff6004 != 0) {
    DAT_00ff60a9 = '\x01';
    FUN_00001098();
    if ((DAT_00ff6004 & 0x40) != 0) {
      FUN_00006200();
      bVar2 = (byte)unaff_D2;
      if ('\v' < (char)bVar2) {
        if ('\x1d' < (char)bVar2) {
          return;
        }
        FUN_00027f18();
        DAT_00ff605b = DAT_00ff606b;
        DAT_00ff606b = bVar2;
        FUN_00008d48();
        FUN_00006928();
        FUN_00006986();
        FUN_00006c86();
        DAT_00ff6085 = 7;
        return;
      }
      FUN_00027f18();
      if (*(char *)(unaff_A2 + 0xc) != '\0') {
        return;
      }
      if ((DAT_00ffe1e0 & 1 << (unaff_D2 & 0x1f)) == 0) {
        return;
      }
      iVar1 = (int)(short)((ushort)bVar2 << 6);
      DAT_00ff610f = (&DAT_00006c68)[(short)(ushort)(byte)((&DAT_00ffe7a4)[iVar1] - 1)];
      if ((&DAT_00ffe7aa)[iVar1] == 'w') {
        DAT_00ff610f = 0x6f;
      }
      else if ((&DAT_00ffe7aa)[iVar1] == 'x') {
        DAT_00ff610f = 0x5f;
      }
      DAT_00ff605f = 0;
      DAT_00ff606b = bVar2;
      DAT_00ff606c = 0x1f;
      DAT_00ff6085 = 1;
      DAT_00ff608a = *(undefined2 *)((int)&DAT_00ffe780 + iVar1 + 2);
      DAT_00ff608c = *(undefined2 *)((int)&DAT_00ffe784 + iVar1);
      return;
    }
    if ((DAT_00ff6004 & 0x10) != 0) {
      FUN_00027f18();
      FUN_0000682e();
      return;
    }
    if ((DAT_00ff6004 & 0x20) != 0) {
      FUN_00027f18();
      FUN_00017140();
      return;
    }
  }
  if ((DAT_00ff6004 & 0x80) == 0) {
    if ((DAT_00ff6003 & 4) == 0) {
      if ((DAT_00ff6003 & 8) == 0) {
        if ((DAT_00ff6003 & 1) == 0) {
          if (((DAT_00ff6003 & 2) != 0) && ((short)DAT_00ff604a < 0x140)) {
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
    FUN_00027f18();
    FUN_00025538();
  }
  return;
}

