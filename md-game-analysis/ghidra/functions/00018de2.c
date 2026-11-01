/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00018de2 */

void FUN_00018de2(void)

{
  undefined2 *unaff_A2;
  
  if ((DAT_00ff615d & 4) != 0) {
    unaff_A2[1] = *(undefined2 *)(&DAT_00018e18 + (short)((ushort)DAT_00ff6061 << 1));
    *unaff_A2 = 0x100;
    unaff_A2[2] = 0x53;
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

