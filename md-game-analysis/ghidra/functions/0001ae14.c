/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001ae14 */

void FUN_0001ae14(void)

{
  undefined2 *unaff_A2;
  
  if ((DAT_00ff615d & 0x80) != 0) {
    *unaff_A2 = 0xf3;
    unaff_A2[1] = 0x84;
    unaff_A2[2] = (ushort)(byte)(DAT_00ff6188 + 0x60);
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

