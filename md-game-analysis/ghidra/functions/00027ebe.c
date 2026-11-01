/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00027ebe */

void FUN_00027ebe(void)

{
  DAT_00ff6d00 = (ushort)(byte)(&DAT_00027ee4)[(short)(ushort)DAT_00ffe10f];
  DAT_00ffe11a = DAT_00ff6d00;
  FUN_001e41d4();
  return;
}

