/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000004ba */

void ResetEntry(void)

{
  byte bVar1;
  short sVar2;
  undefined4 *puVar3;
  undefined2 *puVar4;
  
  bVar1 = DAT_00a10001;
  if ((bVar1 & 0xf) != 0) {
    Ram00a14000 = 0x53454741;
  }
  Ram00c00004 = 0x8134;
  Ram00c00004 = 0x8f02;
  Ram00c00004 = 0xc0000000;
  sVar2 = 0x3f;
  do {
    Ram00c00000 = 0;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  DAT_00a10009 = 0x40;
  DAT_00a1000b = 0x40;
  DAT_00a1000d = 0x40;
  sVar2 = 0x12;
  puVar4 = &DAT_000293c4;
  do {
    Ram00c00004 = *puVar4;
    sVar2 = sVar2 + -1;
    puVar4 = puVar4 + 1;
  } while (sVar2 != -1);
  sVar2 = 0x3ffc;
  puVar3 = &DAT_ffff0000;
  do {
    *puVar3 = 0;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
  } while (sVar2 != -1);
  Ram00c00004 = 0x93ff;
  Ram00c00004 = 0x947f;
  Ram00c00004 = 0x9500;
  Ram00c00004 = 0x9600;
  Ram00c00004 = 0x9770;
  Ram00c00004 = 0x40000080;
  do {
    bVar1 = DAT_00c00005;
  } while ((bVar1 & 2) != 0);
  Ram00c00004 = 0x74000003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x74020003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40000010;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40020010;
  Ram00c00000 = 0;
  FUN_00028046();
  FUN_001e3a00();
  FUN_000280d4();
  FUN_001e7618();
  Ram00c00004 = 0x8174;
  FUN_00027fb8();
  DAT_00400000 = 0x60;
  DAT_00ff6d00 = 0xb;
  FUN_001e41d4();
  FUN_000273cc();
  FUN_00027ae8();
  sVar2 = 0x12;
  puVar4 = &DAT_00028162;
  do {
    Ram00c00004 = *puVar4;
    sVar2 = sVar2 + -1;
    puVar4 = puVar4 + 1;
  } while (sVar2 != -1);
  FUN_000010e0();
  FUN_00000e40();
  Seed_e50();
  if (DAT_00ff611b != '\0') {
    FUN_00026ce6();
  }
  Seed_17698();
  FUN_0000151e();
  Seed_7622();
  Seed_18274();
  DAT_00ff610d = 7;
  DAT_00ff610e = 7;
  DAT_00ff601b = 7;
  DAT_00ff601c = 0xf;
  DAT_00ff6036 = 1;
  DAT_00ffe10d = 2;
  DAT_00ffe10e = 2;
  DAT_00ffe116 = '\0';
  DAT_00ffe1f0 = DAT_00ffe780._2_2_;
  DAT_00ffe1f2 = DAT_00ffe784._0_2_;
  DAT_00ff606b = 0;
  FUN_00002be0();
  DAT_00ff601a = 0;
  DAT_00ff6019 = 2;
  DAT_00ffe1e4 = 7;
  DAT_00ffe1ec = 0;
  DAT_00ffe1e8 = 0xf000;
  DAT_00ffe1e0 = 0x3fffffff;
  DAT_00ffe110 = 0x96;
  DAT_00ff6100 = DAT_00c00008;
  DAT_00ff6120 = 1;
  FUN_00006912();
  DAT_00ffe1f5 = 0xff;
  DAT_00ffe600 = 1;
  DAT_00ffe11c = 0x243;
  DAT_00ff6036 = 0;
  DAT_00ff6138 = 0x41;
  DAT_00ff6182 = DAT_00ffe100;
  DAT_00ff603d = DAT_00ff603d | 1;
  FUN_0001201a();
  DAT_00ffe1f6 = DAT_00ffe10e;
  do {
    while (DAT_00ffe116 == '\0') {
      FUN_00000e40();
      FUN_0001a590();
      FUN_000028c2();
      FUN_0000298a();
      FUN_00002a52();
      FUN_00002b1a();
      FUN_0000c438();
      FUN_00025184();
      FUN_00003a82();
      FUN_0000379e();
      FUN_0000f20a();
      FUN_0000f440();
      FUN_0001a5b0();
      FUN_0000f842();
      FUN_0000f9e6();
      FUN_0000fc84();
      FUN_0000fca8();
      FUN_00027dc6();
      FUN_0000097a();
      FUN_00006290();
      FUN_00003e44();
      FUN_00003cb0();
      FUN_000063f8();
      FUN_00003b66();
      FUN_000036cc();
      FUN_0000775c();
      FUN_000011e2();
      FUN_00025270();
    }
    FUN_00000e40();
    FUN_0001a590();
    FUN_000028c2();
    FUN_0000298a();
    FUN_00002a52();
    FUN_00002b1a();
    FUN_0000c438();
    FUN_00003a82();
    FUN_0000f20a();
    FUN_0000f440();
    FUN_0000f842();
    FUN_0000f9e6();
    FUN_0000fc84();
    FUN_0000fca8();
    FUN_00027dc6();
    FUN_00012074();
    FUN_00007d40();
    FUN_000043ca();
    FUN_000251ee();
    FUN_0000379e();
    FUN_0000cfdc();
    FUN_0000c494();
    FUN_0000d962();
    FUN_0000c7ec();
    FUN_00009f2e();
    FUN_000153d4();
    FUN_0001611a();
    FUN_0000a138();
    FUN_0000a432();
    FUN_0000dbf0();
    FUN_00007e98();
    FUN_00014c12();
    FUN_00006588();
    FUN_000075aa();
    FUN_000073b8();
    FUN_00006790();
    FUN_00007348();
    FUN_0001683e();
    FUN_00016ac6();
    FUN_00003ae4();
    FUN_0000622e();
    FUN_00007b8e();
    FUN_0000a8da();
    FUN_0000b2f2();
    FUN_00014aea();
    FUN_0002582a();
  } while( true );
}

