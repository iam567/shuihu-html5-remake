/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00027dc6 */

void FUN_00027dc6(void)

{
  if (DAT_00ff6046 != '\0') {
    DAT_00ff6046 = '\0';
    DAT_00ff6d00 = (ushort)*(byte *)(*(int *)(&DAT_00027e16 + (short)(((DAT_00ffe100 >> 8) - 1) * 4)
                                             ) + (int)(short)(DAT_00ffe100 & 0xff));
    FUN_001e41d4();
    DAT_00ffe11a = DAT_00ff6d00;
  }
  return;
}

