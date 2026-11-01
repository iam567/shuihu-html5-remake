/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001201a */

void FUN_0001201a(void)

{
  DAT_00ff6130 = (int)*(short *)(*(int *)(&DAT_000e2de2 + (short)((DAT_00ff6182 >> 8) << 2)) +
                                (int)(short)((ushort)DAT_00ff6138 << 1)) +
                 *(int *)(&DAT_000e2de2 + (short)((DAT_00ff6182 >> 8) << 2));
  return;
}

