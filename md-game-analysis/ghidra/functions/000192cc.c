/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000192cc */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000192cc(void)

{
  short sVar1;
  undefined4 *puVar2;
  
  DAT_00ff613f = DAT_00ffe631;
  DAT_00ff60b6 = 0x22;
  DAT_00ff60b4 = 0xa00a;
  FUN_000144b8();
  DAT_00ff60b4 = 0x1001;
  FUN_000144b8();
  sVar1 = 0xb;
  puVar2 = (undefined4 *)&DAT_00ff1000;
  do {
    *puVar2 = 0;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (sVar1 != -1);
  DAT_00ff1000 = DAT_00ffe630;
  DAT_00ff1004._3_1_ = DAT_00ffe631;
  _DAT_00ff1008 = DAT_00ffe632;
  DAT_00ff1010 = DAT_00ffe636;
  DAT_00ff1024 = DAT_00ffe638;
  DAT_00ff102a = DAT_00ffe639;
  _DAT_00ff1026 = DAT_00ffe63a;
  DAT_00ff1021 = DAT_00ffe63e;
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

