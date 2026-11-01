/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00005cc6 */

void FUN_00005cc6(void)

{
  DAT_00ff60b2 = (&DAT_00028e56)[(short)((ushort)(byte)(DAT_00ff60bc - 1) << 3)] + -1;
  return;
}

