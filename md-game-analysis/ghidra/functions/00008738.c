/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00008738 */

void FUN_00008738(void)

{
  DAT_00ff60b2 = (&DAT_00028e56)
                 [(short)((ushort)(byte)((&DAT_00ffe7a6)[(short)((ushort)DAT_00ff606b << 6)] - 1) <<
                         3)] + -1;
  return;
}

