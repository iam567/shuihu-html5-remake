/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000b46a */

void FUN_0000b46a(void)

{
  undefined2 *unaff_A2;
  
  if (DAT_00ff60ad != 0) {
    DAT_00ff60ad = DAT_00ff60ad - 1;
    *unaff_A2 = DAT_00ff60ae;
    unaff_A2[1] = DAT_00ff60b0;
    unaff_A2[2] = (ushort)(byte)((DAT_00ff60ad >> 2) + 0x40);
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

