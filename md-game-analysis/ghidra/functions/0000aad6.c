/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000aad6 */

void FUN_0000aad6(void)

{
  char in_D0b;
  char in_D1b;
  char unaff_D2b;
  byte bVar1;
  char unaff_D6b;
  byte bVar2;
  byte *unaff_A2;
  byte *unaff_A3;
  byte *unaff_A4;
  byte *unaff_A5;
  char in_XF;
  
  bVar1 = in_D1b * '\x03' + unaff_D2b + in_XF * '\x03';
  bVar2 = in_D0b + unaff_D6b + in_XF;
  *unaff_A2 = bVar1 & *unaff_A2;
  *unaff_A3 = bVar1 & *unaff_A3;
  *unaff_A4 = bVar1 & *unaff_A4;
  *unaff_A5 = bVar1 & *unaff_A5;
  *unaff_A3 = bVar2 & *unaff_A3;
  *unaff_A2 = bVar2 & *unaff_A2;
  *unaff_A5 = bVar2 & *unaff_A5;
  *unaff_A4 = bVar2 & *unaff_A4;
  *unaff_A4 = bVar1 + *unaff_A4;
  *unaff_A5 = bVar1 + *unaff_A5;
  *unaff_A2 = bVar1 + *unaff_A2;
  *unaff_A3 = bVar1 + *unaff_A3;
  *unaff_A5 = bVar2 + *unaff_A5;
  *unaff_A4 = bVar2 + *unaff_A4;
  *unaff_A3 = bVar2 + *unaff_A3;
  *unaff_A2 = bVar2 + *unaff_A2;
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

