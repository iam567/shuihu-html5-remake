/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000144f8 */

void FUN_000144f8(void)

{
  DAT_00ff613f = *(undefined1 *)((int)&DAT_00ffe784 + (short)((ushort)DAT_00ff60c8._0_1_ << 6) + 3);
  DAT_00ff60b6 = 0x22;
  DAT_00ff60b4 = 0xa00a;
  FUN_000144b8();
  DAT_00ff60b4 = 0x1001;
  FUN_000144b8();
  return;
}

