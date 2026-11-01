/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001948c */

void FUN_0001948c(void)

{
  undefined2 *unaff_A2;
  
  if ((DAT_00ff615d & 8) != 0) {
    *unaff_A2 = 0x118;
    unaff_A2[1] = 0x85;
    unaff_A2[2] = (ushort)(byte)(DAT_00ff6176 + 0x54);
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

