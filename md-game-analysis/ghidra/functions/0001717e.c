/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001717e */

void FUN_0001717e(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  DAT_00ff6036 = 0;
  FUN_00000ef0();
  DAT_00ff615a = DAT_00ff6018;
  DAT_00ff6018 = 0;
  DAT_00ffe116 = 0xff;
  FUN_00001098();
  FUN_000010ac();
  FUN_000010c8();
  sVar1 = 0x12;
  puVar2 = &DAT_00017608;
  do {
    Ram00c00004 = *puVar2;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (sVar1 != -1);
  Ram00c00004 = 0x74000003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x74020003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40000010;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40020010;
  Ram00c00000 = 0;
  DAT_00ff600a = 0;
  DAT_00ff6034 = 0;
  DAT_00ff6035 = 0;
  FUN_000010e0();
  FUN_00000e40();
  Seed_e50();
  Seed_e50();
  Seed_1028();
  Seed_1060();
  DAT_00ff60e8 = (int)&DAT_00ffe780 + (int)(short)((ushort)DAT_00ff606b << 6);
  DAT_00ff613f = *(undefined1 *)((int)&DAT_00ffe784 + (short)((ushort)DAT_00ff606b << 6) + 3);
  DAT_00ff60b6 = 0x22;
  DAT_00ff60b4 = 0xa00a;
  FUN_000144b8();
  DAT_00ff60b4 = 0x1001;
  FUN_000144b8();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_00002846();
  FUN_00000e7c();
  do {
    FUN_00000e40();
    if ((DAT_00ff6004 & 0x20) != 0) break;
  } while ((DAT_00ff6004 & 0x10) == 0);
  FUN_00000ef0();
  sVar1 = 0x12;
  puVar2 = &DAT_00028162;
  do {
    Ram00c00004 = *puVar2;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (sVar1 != -1);
  DAT_00ff6034 = 0;
  DAT_00ff6035 = 0;
  DAT_00ff6008 = 0;
  DAT_00ff600a = 0;
  DAT_00ff600c = 0;
  DAT_00ff600e = 0;
  FUN_00001098();
  FUN_000010ac();
  FUN_00002d00();
  FUN_00002e84();
  FUN_00025d46();
  FUN_00002ffc();
  DAT_00ffe116 = 1;
  DAT_00ff6018 = DAT_00ff615a;
  DAT_00ff6019 = DAT_00ff6019 | 2;
  DAT_00ff601a = 0;
  DAT_00ff601b = 1;
  DAT_00ff601c = 0xf;
  DAT_00ff6036 = 0xff;
  return;
}

