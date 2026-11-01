/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00008d92 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00008d92(void)

{
  int iVar1;
  short extraout_D1w;
  short extraout_D1w_00;
  short extraout_D1w_01;
  short extraout_D1w_02;
  ushort uVar2;
  ushort extraout_D1w_03;
  ushort extraout_D1w_04;
  short extraout_D1w_05;
  int unaff_A2;
  
  if (*(char *)(unaff_A2 + 0x20) == '\0') {
    _DAT_00ff6088 = *(undefined2 *)(unaff_A2 + 0x22);
    FUN_00009516();
  }
  else if (*(char *)(unaff_A2 + 0x20) == '\x01') {
    FUN_000092c2();
    _DAT_00ff6088 =
         CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + (short)(extraout_D1w << 6) + 2) >> 5),
                  (char)(*(ushort *)((int)&DAT_00ffe784 + (int)(short)(extraout_D1w << 6)) >> 5));
    FUN_00009516();
  }
  else if (*(char *)(unaff_A2 + 0x20) == '\x02') {
    FUN_000097dc();
    if (DAT_00ff7180 != -1) {
      FUN_00009192();
      iVar1 = (int)(short)(extraout_D1w_00 << 6);
      DAT_00ff60be = (&DAT_00ffe7a4)[iVar1];
      _DAT_00ff6088 =
           CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + iVar1 + 2) >> 5),
                    (char)(*(ushort *)((int)&DAT_00ffe784 + iVar1) >> 5));
      FUN_00009516();
      FUN_000099fa();
      return;
    }
    _DAT_00ff6088 = *(undefined2 *)(unaff_A2 + 0x22);
    FUN_00009516();
  }
  else if (*(char *)(unaff_A2 + 0x20) == '\x03') {
    FUN_000097dc();
    if (DAT_00ff7180 != -1) {
      FUN_00009192();
      iVar1 = (int)(short)(extraout_D1w_02 << 6);
      DAT_00ff60be = (&DAT_00ffe7a4)[iVar1];
      _DAT_00ff6088 =
           CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + iVar1 + 2) >> 5),
                    (char)(*(ushort *)((int)&DAT_00ffe784 + iVar1) >> 5));
      FUN_00009516();
      FUN_000099fa();
      return;
    }
    FUN_000092c2();
    _DAT_00ff6088 =
         CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + (short)(extraout_D1w_01 << 6) + 2) >> 5),
                  (char)(*(ushort *)((int)&DAT_00ffe784 + (int)(short)(extraout_D1w_01 << 6)) >> 5))
    ;
    FUN_00009516();
  }
  else if (*(char *)(unaff_A2 + 0x20) == '\x04') {
    FUN_00009912();
    FUN_000092f8();
    if (DAT_00ff60bd == 0xff) {
      _DAT_00ff6088 = *(undefined2 *)(unaff_A2 + 0x22);
      FUN_00009516();
    }
    else {
      _DAT_00ff6088 =
           CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff60bd << 6) + 2)
                          >> 5),
                    (char)(*(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff60bd << 6))
                          >> 5));
      FUN_00009516();
    }
  }
  else if (*(char *)(unaff_A2 + 0x20) == '\x05') {
    FUN_00009912();
    FUN_000092f8();
    uVar2 = (ushort)DAT_00ff60bd;
    if (DAT_00ff60bd == 0xff) {
      FUN_000092c2();
      uVar2 = extraout_D1w_03;
    }
    _DAT_00ff6088 =
         CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + (short)(uVar2 << 6) + 2) >> 5),
                  (char)(*(ushort *)((int)&DAT_00ffe784 + (int)(short)(uVar2 << 6)) >> 5));
    FUN_00009516();
  }
  else if (*(char *)(unaff_A2 + 0x20) == '\x06') {
    FUN_0000cbb0();
    FUN_0000cdd0();
    if (DAT_00ff6108 == 0xff) {
      _DAT_00ff6088 = *(undefined2 *)(unaff_A2 + 0x22);
      FUN_00009516();
    }
    else {
      _DAT_00ff6088 =
           CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff6108 << 6) + 2)
                          >> 5),
                    (char)(*(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff6108 << 6))
                          >> 5));
      FUN_00009516();
    }
  }
  else if (*(char *)(unaff_A2 + 0x20) == '\a') {
    FUN_0000cbb0();
    FUN_0000cdd0();
    uVar2 = (ushort)DAT_00ff6108;
    if (DAT_00ff6108 == 0xff) {
      FUN_000092c2();
      uVar2 = extraout_D1w_04;
    }
    _DAT_00ff6088 =
         CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + (short)(uVar2 << 6) + 2) >> 5),
                  (char)(*(ushort *)((int)&DAT_00ffe784 + (int)(short)(uVar2 << 6)) >> 5));
    FUN_00009516();
  }
  else if (*(char *)(unaff_A2 + 0x20) == '\b') {
    FUN_0000916c();
    FUN_0000d48c();
    FUN_0000d3d2();
    if (DAT_00ff610b == 0xff) {
      _DAT_00ff6088 = *(undefined2 *)(unaff_A2 + 0x22);
      FUN_00009516();
    }
    else {
      _DAT_00ff6088 =
           CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff610b << 6) + 2)
                          >> 5),
                    (char)(*(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff610b << 6))
                          >> 5));
      FUN_00009516();
    }
  }
  else if (*(char *)(unaff_A2 + 0x20) == '\t') {
    FUN_0000916c();
    FUN_0000d48c();
    FUN_0000d3d2();
    if (DAT_00ff610b != 0xff) {
      _DAT_00ff6088 =
           CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff610b << 6) + 2)
                          >> 5),
                    (char)(*(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff610b << 6))
                          >> 5));
      FUN_00009516();
      FUN_0000d59c();
      return;
    }
    FUN_000092c2();
    _DAT_00ff6088 =
         CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + (short)(extraout_D1w_05 << 6) + 2) >> 5),
                  (char)(*(ushort *)((int)&DAT_00ffe784 + (int)(short)(extraout_D1w_05 << 6)) >> 5))
    ;
    FUN_00009516();
  }
  FUN_0000972e();
  return;
}

