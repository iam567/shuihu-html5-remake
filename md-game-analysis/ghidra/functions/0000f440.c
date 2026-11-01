/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000f440 */

void FUN_0000f440(void)

{
  uint uVar1;
  byte bVar2;
  
  if ((DAT_00ff6123 != 0) && (DAT_00ff612a == '\0')) {
    if ((char)DAT_00ff6123 < '\a') {
      if ((DAT_00ff6123 & 1) != 0) {
        DAT_00ff6124 = 0;
        FUN_0000f772();
        DAT_00ff6124 = 0;
        FUN_0000f772();
        FUN_0000f65a();
      }
      DAT_00ff6123 = DAT_00ff6123 + 1;
    }
    else {
      DAT_00ff6123 = 0;
      FUN_00001098();
      bVar2 = DAT_00ff603d;
      if ((DAT_00ff6160 == '\0') || (DAT_00ff6160 != -1)) {
        DAT_00ff603d = DAT_00ff603d | 2;
        if ((bVar2 & 1) == 0) {
          DAT_00ff6036 = 0xff;
          uVar1 = (uint)DAT_00ff606f;
          bVar2 = DAT_00ff606f << 4;
          (&DAT_00ffe081)[(short)(ushort)bVar2] = DAT_00ff6161;
          (&DAT_00ffe086)[(short)(ushort)bVar2] = DAT_00ff6162;
          DAT_00ff601e._0_1_ = DAT_00ff601e._0_1_ | '\x01' << (uVar1 & 7);
          if (DAT_00ff6160 != '\0') {
            FUN_0001c552();
          }
        }
      }
      else {
        DAT_00ff6121 = *DAT_00ff612c;
        DAT_00ff613f = *DAT_00ff612c;
        DAT_00ff6128 = 0;
        DAT_00ff6127 = 1;
        DAT_00ff6126 = 0xff;
        if (DAT_00ff6121 == '\0') {
          DAT_00ff612c = DAT_00ff612c + 1;
          FUN_0001977c();
        }
        else {
          DAT_00ff612c = DAT_00ff612c + 1;
          FUN_00002846();
        }
        DAT_00ff6122 = 1;
      }
    }
  }
  return;
}

