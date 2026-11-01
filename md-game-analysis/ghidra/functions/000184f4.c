/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000184f4 */

void FUN_000184f4(void)

{
  byte bVar1;
  short sVar2;
  uint uVar3;
  bool bVar4;
  
  DAT_00ff6036 = 0;
  FUN_00000ef0();
  DAT_00ff615a = DAT_00ff6018;
  DAT_00ff6018 = 0;
  DAT_00ffe116 = 0xff;
  FUN_00001098();
  FUN_000010ac();
  FUN_000010c8();
  DAT_00ff615d = DAT_00ff615d | 2;
  DAT_00ff6189 = DAT_00ff6189 | 1;
  Ram00c00004 = 0x74000003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x74020003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40000010;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40020010;
  Ram00c00000 = 0;
  DAT_00ff6034 = 0;
  DAT_00ff6035 = 0;
  FUN_000010e0();
  FUN_00000e40();
  Seed_e50();
  Seed_e50();
  Seed_e50();
  Seed_1028();
  Seed_1060();
  DAT_00ff60b6 = 0;
  DAT_00ff60b4 = 0x2002;
  FUN_000144b8();
  FUN_000144b8();
  uVar3 = 0;
  DAT_00ffe1f4 = 0;
  sVar2 = 0x13;
  do {
    if ((DAT_00ff616c & 1 << (uVar3 & 0x1f)) != 0) {
      DAT_00ffe1f4 = DAT_00ffe1f4 + 1;
    }
    uVar3 = (uint)(byte)((char)uVar3 + 1);
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  FUN_000144b8();
  FUN_00018aaa();
  DAT_00ff6168 = 0xfffff;
  FUN_00018b8c();
  DAT_00ff6163 = 0;
  DAT_00ff6164 = 0x118;
  DAT_00ff6166 = 0x80;
  FUN_000180e6();
  FUN_00018c18();
  FUN_00000e7c();
LAB_000186f2:
  while( true ) {
    while( true ) {
      FUN_00000e40();
      FUN_00018b8c();
      FUN_000180e6();
      if ((DAT_00ff6004 & 1) == 0) break;
      FUN_00027f08();
      if (3 < DAT_00ff6163) {
        bVar1 = DAT_00ff6163 - 4;
        goto LAB_000187ca;
      }
    }
    if ((DAT_00ff6004 & 2) != 0) goto code_r0x00018736;
    if ((DAT_00ff6004 & 4) == 0) break;
    FUN_00027f08();
    if (DAT_00ff6163 != 0) {
      bVar1 = DAT_00ff6163 - 1;
      goto LAB_000187ca;
    }
  }
  if ((DAT_00ff6004 & 8) == 0) {
    if ((DAT_00ff6004 & 0x40) == 0) {
      if ((DAT_00ff6004 & 0x80) != 0) {
        FUN_00027f18();
        DAT_00ff615d = DAT_00ff615d | 4;
        DAT_00ff6061 = '\0';
        do {
          FUN_00000e40();
          FUN_000180e6();
          DAT_00ff6061 = DAT_00ff6061 + '\x01';
        } while (DAT_00ff6061 != '\n');
        DAT_00ff6061 = '\t';
        do {
          FUN_00000e40();
          FUN_000180e6();
          if (((DAT_00ff6004 & 0x80) != 0) || ((DAT_00ff6004 & 0x40) != 0)) {
            FUN_00027f18();
            FUN_00000ef0();
            uVar3 = 0;
            DAT_00ffe1e4 = 0;
            sVar2 = DAT_00ffe1f4 - 1;
            do {
              DAT_00ffe1e4 = DAT_00ffe1e4 | 1 << (uVar3 & 0x1f);
              uVar3 = (uint)(byte)((char)uVar3 + 1);
              sVar2 = sVar2 + -1;
            } while (sVar2 != -1);
            return;
          }
        } while ((DAT_00ff6004 & 0x10) == 0);
        FUN_00027f18();
        do {
          FUN_00000e40();
          FUN_000180e6();
          bVar4 = DAT_00ff6061 != '\0';
          DAT_00ff6061 = DAT_00ff6061 + -1;
        } while (bVar4);
        DAT_00ff615d = DAT_00ff615d & 0xfb;
        DAT_00ff6061 = 0xff;
      }
      goto LAB_000186f2;
    }
    FUN_00027f18();
    bVar1 = DAT_00ff6163;
    sVar2 = (ushort)DAT_00ff6163 << 6;
    if ((&DAT_00ff801d)[sVar2] == '\0') {
      if ((DAT_00ff616c & 1 << (DAT_00ff6163 & 0x1f)) != 0) goto LAB_000186f2;
      (&DAT_00ff801d)[sVar2] = 1;
      DAT_00ff6168 = DAT_00ff6168 | 1 << (bVar1 & 0x1f);
      DAT_00ffe1f4 = DAT_00ffe1f4 - 1;
      DAT_00ff6170 = DAT_00ff6170 & ~(1 << (bVar1 & 0x1f));
    }
    else {
      if (DAT_00ffe1f4 == DAT_00ff6175) goto LAB_000186f2;
      (&DAT_00ff801d)[sVar2] = 0;
      DAT_00ff6168 = DAT_00ff6168 | 1 << (bVar1 & 0x1f);
      DAT_00ffe1f4 = DAT_00ffe1f4 + 1;
      DAT_00ff6170 = DAT_00ff6170 | 1 << (bVar1 & 0x1f);
    }
    DAT_00ff60b6 = 0;
    DAT_00ff60b4 = 0x2002;
    FUN_000144b8();
    goto LAB_000186f2;
  }
  FUN_00027f08();
  if ((DAT_00ff6163 == 0x13) || (bVar1 = DAT_00ff6163 + 1, DAT_00ffe115 <= (byte)(DAT_00ff6163 + 1))
     ) goto LAB_000186f2;
LAB_000187ca:
  DAT_00ff6163 = bVar1;
  DAT_00ff6166 = (DAT_00ff6163 / 4) * 0x28 + 0x80;
  DAT_00ff6164 = ((ushort)DAT_00ff6163 % 4) * 0x28 + 0x118;
  FUN_00018c18();
  goto LAB_000186f2;
code_r0x00018736:
  FUN_00027f08();
  if ((0xf < DAT_00ff6163) || (bVar1 = DAT_00ff6163 + 4, DAT_00ffe115 <= (byte)(DAT_00ff6163 + 4)))
  goto LAB_000186f2;
  goto LAB_000187ca;
}

