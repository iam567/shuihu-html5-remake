/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00024f06 */

void FUN_00024f06(void)

{
  uint uVar1;
  short sVar2;
  uint uVar3;
  short extraout_D1w;
  short sVar4;
  undefined4 *puVar5;
  short *psVar6;
  byte *pbVar7;
  
  sVar2 = 0x1df;
  puVar5 = &DAT_00ffe780;
  do {
    *puVar5 = 0;
    uVar1 = DAT_00ff6170;
    sVar2 = sVar2 + -1;
    puVar5 = puVar5 + 1;
  } while (sVar2 != -1);
  puVar5 = &DAT_00ffe780;
  pbVar7 = &DAT_00ffe610;
  uVar3 = 0;
  sVar2 = 0x13;
  do {
    if (*pbVar7 == 0) break;
    if ((uVar1 & 1 << (uVar3 & 0x1f)) != 0) {
      sVar4 = (*pbVar7 - 1) * 0x10;
      *(undefined1 *)puVar5 = (&DAT_00ffe630)[sVar4];
      *(undefined1 *)((int)puVar5 + 7) = (&DAT_00ffe631)[sVar4];
      puVar5[2] = *(undefined4 *)((int)&DAT_00ffe632 + (int)sVar4);
      *(undefined1 *)(puVar5 + 4) = *(undefined1 *)((int)&DAT_00ffe636 + (int)sVar4);
      *(undefined1 *)((int)puVar5 + 0x11) = *(undefined1 *)((int)&DAT_00ffe636 + sVar4 + 1);
      *(undefined1 *)(puVar5 + 9) = (&DAT_00ffe638)[sVar4];
      *(undefined1 *)((int)puVar5 + 0x2a) = (&DAT_00ffe639)[sVar4];
      *(undefined4 *)((int)puVar5 + 0x26) = *(undefined4 *)((int)&DAT_00ffe63a + (int)sVar4);
      *(undefined1 *)((int)puVar5 + 0x21) = (&DAT_00ffe63e)[sVar4];
      *(undefined1 *)((int)puVar5 + 1) = 4;
      *(undefined1 *)((int)puVar5 + 6) = 1;
      puVar5 = puVar5 + 0x10;
    }
    pbVar7 = pbVar7 + 1;
    uVar3 = (uint)(ushort)((short)uVar3 + 1);
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  sVar2 = 0;
  do {
    if (DAT_00ffe780._0_1_ == '\0') break;
    sVar4 = FUN_00014c80();
    *(undefined2 *)((int)&DAT_00ffe792 + (int)(short)(sVar2 << 6)) =
         *(undefined2 *)((int)&DAT_00ffe79e + (int)(short)(sVar2 << 6));
    sVar2 = extraout_D1w + 1;
  } while (sVar4 != 0);
  psVar6 = (short *)&DAT_00ffe780;
  sVar2 = 0x13;
  do {
    if (*psVar6 == 0) break;
    *(undefined *)((int)psVar6 + 0x2b) =
         (&DAT_00028e55)[(short)((*(byte *)(psVar6 + 0x13) - 1) * 8)];
    *(undefined *)(psVar6 + 0x16) =
         (&DAT_00028e55)[(short)((*(byte *)((int)psVar6 + 0x27) - 1) * 8)];
    *(undefined *)((int)psVar6 + 0x2d) =
         (&DAT_00028e55)[(short)((*(byte *)(psVar6 + 0x14) - 1) * 8)];
    *(undefined *)(psVar6 + 0x17) =
         (&DAT_00028e55)[(short)((*(byte *)((int)psVar6 + 0x29) - 1) * 8)];
    psVar6 = psVar6 + 0x20;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  FUN_0001c898();
  DAT_00ff6014 = (ushort)DAT_00ffe104 << 5;
  DAT_00ff6016 = (ushort)DAT_00ffe105 << 5;
  DAT_00ff6034 = 0;
  DAT_00ff6035 = 0;
  DAT_00ff6008 = 0;
  DAT_00ff600a = 0;
  DAT_00ff600c = 0;
  DAT_00ff600e = 0;
  Ram00c00004 = 0x74020003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40020010;
  Ram00c00000 = 0;
  Ram00c00004 = 0x74000003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40000010;
  Ram00c00000 = 0;
  FUN_00001098();
  FUN_00002d00();
  FUN_00002e84();
  FUN_00025d46();
  FUN_00002d80();
  FUN_000068ba();
  FUN_00002ffc();
  FUN_0001a552();
  FUN_00024b60();
  DAT_00ffe1e0 = 0x3fffffff;
  DAT_00ff615d = 0;
  DAT_00ff6189 = 0;
  DAT_00ff6019 = DAT_00ff6019 | 2;
  DAT_00ff601a = 0;
  DAT_00ff601b = 1;
  DAT_00ff601c = 0xf;
  DAT_00ffe116 = 1;
  DAT_00ffe1f7 = 0;
  DAT_00ff6085 = 0;
  DAT_00ffe10e = 4;
  DAT_00ffe10d = 2;
  DAT_00ffe1f0 = DAT_00ffe780._2_2_;
  DAT_00ffe1f2 = DAT_00ffe784._0_2_;
  DAT_00ff606b = 0;
  DAT_00ff6120 = 1;
  DAT_00ffe1f5 = 0xff;
  return;
}

