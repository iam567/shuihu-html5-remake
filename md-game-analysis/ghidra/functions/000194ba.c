/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000194ba */

void FUN_000194ba(void)

{
  undefined2 *unaff_A2;
  
  if ((DAT_00ff615d & 0x10) != 0) {
    *unaff_A2 = *(undefined2 *)(&DAT_000194f8 + (short)((ushort)DAT_00ff6177 << 1));
    unaff_A2[1] = 0x88;
    unaff_A2[2] = (ushort)(byte)(DAT_00ff6177 + 0x58);
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

