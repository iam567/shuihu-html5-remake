/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007c14 */

void FUN_00007c14(void)

{
  DAT_00ffe1f6 = DAT_00ffe10e;
  DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2) >> 5;
  DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6)) >> 5;
  DAT_00ff605a = 1;
  DAT_00ff6036 = 0;
  DAT_00ffe10e = 8;
  return;
}

