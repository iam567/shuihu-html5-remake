/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000a8a0 */

void FUN_0000a8a0(void)

{
  int unaff_A2;
  
  DAT_00ff6152 = 0x32;
  if (((&DAT_00ffe7a7)[(short)((ushort)DAT_00ff606b << 6)] != '`') &&
     (DAT_00ff6152 = 100, (&DAT_00ffe7a7)[(short)((ushort)DAT_00ff606b << 6)] != 'a')) {
    DAT_00ff6152 = *(undefined2 *)(unaff_A2 + 0x1e);
  }
  return;
}

