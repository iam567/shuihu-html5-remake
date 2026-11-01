/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000ca16 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0000ca16(void)

{
  undefined1 uVar1;
  short sVar2;
  byte bVar3;
  
  FUN_00002846();
  FUN_00002846();
  if (DAT_00ff60c8 < 0xff) {
    FUN_00002846();
  }
  FUN_00006772();
  DAT_00ff60c0._0_2_ =
       CONCAT11((char)((ushort)DAT_00ff6056 >> 8),(char)DAT_00ff6056 - DAT_00ffe104) << 2;
  sVar2 = CONCAT11((char)((ushort)DAT_00ff6058 >> 8),(char)DAT_00ff6058 - DAT_00ffe105) << 2;
  bVar3 = (byte)sVar2;
  uVar1 = (undefined1)((ushort)sVar2 >> 8);
  _DAT_00ff60c4 = CONCAT11(uVar1,bVar3 - 5);
  if (bVar3 < 5) {
    _DAT_00ff60c4 = CONCAT11(uVar1,bVar3 + 5);
    FUN_00006f50();
    FUN_00006f50();
  }
  else {
    FUN_00006f50();
    FUN_00006f50();
  }
  if (DAT_00ff60c8 != 0) {
    FUN_00006f50();
  }
  return;
}

