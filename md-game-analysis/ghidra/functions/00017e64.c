/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00017e64 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00017e64(void)

{
  int iVar1;
  short sVar2;
  undefined4 *puVar3;
  
  sVar2 = 0xb;
  puVar3 = (undefined4 *)&DAT_00ff1000;
  do {
    *puVar3 = 0;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
  } while (sVar2 != -1);
  iVar1 = (int)(short)((ushort)(byte)((&DAT_00ffe610)[(short)(ushort)DAT_00ff615b] - 1) << 4);
  DAT_00ff1000 = (&DAT_00ffe630)[iVar1];
  DAT_00ff1004._3_1_ = (&DAT_00ffe630)[iVar1];
  _DAT_00ff1008 = *(undefined4 *)((int)&DAT_00ffe632 + iVar1);
  DAT_00ff1010 = *(undefined2 *)((int)&DAT_00ffe636 + iVar1);
  DAT_00ff1024 = (&DAT_00ffe638)[iVar1];
  DAT_00ff102a = (&DAT_00ffe639)[iVar1];
  _DAT_00ff1026 = *(undefined4 *)((int)&DAT_00ffe63a + iVar1);
  DAT_00ff1021 = (&DAT_00ffe63e)[iVar1];
  _DAT_00ff60c4 = 0;
  DAT_00ff60c0 = 0x300;
  if ((DAT_00ff600a & 0x100) == 0) {
    DAT_00ff60c0 = 0x400;
    _DAT_00ff60c4 = 0x20;
  }
  DAT_00ff613f = (&DAT_00ffe631)[iVar1];
  DAT_00ff60b6 = 0x22;
  DAT_00ff60b4 = 0xa00a;
  FUN_000144b8();
  DAT_00ff60b4 = 0x1001;
  FUN_000144b8();
  Seed_1028();
  FUN_00014c80();
  DAT_00ff1012 = DAT_00ff101e;
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
  FUN_00002846();
  return;
}

