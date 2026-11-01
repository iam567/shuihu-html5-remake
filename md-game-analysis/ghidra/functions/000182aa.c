/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000182aa */

void FUN_000182aa(void)

{
  byte *pbVar1;
  
  FUN_000183e8();
  if ((DAT_00ff6037 & 1) != 0) {
    DAT_00ff6121 = (&DAT_00ffe080)[(byte)(DAT_00ff606f << 4)];
    DAT_00ff613f = (&DAT_00ffe087)[(byte)(DAT_00ff606f << 4)];
    if (DAT_00ff613f != 0) {
      FUN_00018478();
      DAT_00ff601e._0_1_ = DAT_00ff601e._0_1_ | '\x01' << (DAT_00ff606f & 7);
      FUN_000011e2();
      pbVar1 = *(byte **)(*(int *)((int)&PTR_PTR_000deb4c + (int)(short)((ushort)DAT_00ff613f << 2))
                         + (int)(short)((ushort)(byte)(&DAT_00ffe300)[(short)(ushort)DAT_00ff613f]
                                       << 2));
      DAT_00ff612c = pbVar1 + 1;
      DAT_00ff613f = *pbVar1;
      DAT_00ff6128 = 0;
      DAT_00ff60b6 = 0xdd;
      DAT_00ff60b4 = 0x1001;
      DAT_00ff6127 = 1;
      DAT_00ff6036 = 0;
      if (DAT_00ff6121 == '\0') {
        FUN_0001977c();
      }
      else {
        FUN_00002846();
      }
      Seed_e50();
      DAT_00ff6122 = 1;
      DAT_00ff6141 = 0x60 < (ushort)(DAT_00ffe004 - DAT_00ff6016);
      if ((ushort)(DAT_00ffe002 - DAT_00ff6014) < 0x41) {
        DAT_00ff6141 = DAT_00ff6141 | 2;
      }
    }
  }
  return;
}

