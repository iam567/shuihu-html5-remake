/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000f842 */

void FUN_0000f842(void)

{
  byte bVar1;
  ushort uVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  if ((((DAT_00ff6126 != '\0') && (DAT_00ff612a == '\0')) && (DAT_00ff6122 == '\0')) &&
     (pbVar4 = DAT_00ff612c, (DAT_00ff612b & (byte)DAT_00ff6010) == 0)) {
    do {
      while( true ) {
        while( true ) {
          pbVar3 = pbVar4 + 1;
          bVar1 = *pbVar4;
          if (bVar1 == 0xff) {
            if ((uint)DAT_00ff6128 % 0x30 == 0) {
              DAT_00ff6123 = 1;
              DAT_00ff6126 = 0;
              DAT_00ff612c = pbVar4 + 2;
              DAT_00ff6160 = *pbVar3;
              return;
            }
            DAT_00ff6123 = 1;
            DAT_00ff6126 = 0;
            DAT_00ff612a = 0xff;
            DAT_00ff612c = pbVar4 + 2;
            DAT_00ff6140 = 0xff;
            DAT_00ff6160 = *pbVar3;
            return;
          }
          if ((bVar1 < 0xf0) || (0xfb < bVar1)) break;
          DAT_00ff60b3 = bVar1 + 0x10;
          pbVar4 = pbVar3;
        }
        if (bVar1 == 0xfe) break;
        if (bVar1 == 0xfc) {
          if (DAT_00ff60b4 == 0x1001) {
            DAT_00ff60b4 = -0x5ff6;
            pbVar4 = pbVar3;
          }
          else {
            DAT_00ff60b4 = 0x1001;
            pbVar4 = pbVar3;
          }
        }
        else {
          if (bVar1 != 0xfd) {
            uVar2 = DAT_00ff6128;
            if (0x2f < DAT_00ff6128) {
              for (; 0x2f < uVar2; uVar2 = uVar2 - 0x30) {
              }
              if ((uVar2 & 0xf) == 0) {
                FUN_0000fac0();
                FUN_0000fb86();
              }
            }
            DAT_00ff612c = pbVar3;
            FUN_0000b970();
            FUN_0000b98c();
            FUN_0000ba5c();
            DAT_00ff6128 = DAT_00ff6128 + 1;
            if (DAT_00ff6128 % 0x30 != 0) {
              return;
            }
            DAT_00ff612a = 0xff;
            DAT_00ff6140 = 0xff;
            return;
          }
          DAT_00ff612b = *pbVar3;
          pbVar4 = pbVar4 + 2;
        }
      }
      DAT_00ff6128 = (DAT_00ff6128 & 0xfff0) + 0x10;
      pbVar4 = pbVar3;
    } while (DAT_00ff6128 % 0x30 != 0);
    DAT_00ff612a = -1;
    DAT_00ff6140 = 0xff;
    DAT_00ff612c = pbVar3;
  }
  return;
}

