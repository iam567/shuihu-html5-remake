/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00025b20 */

void FUN_00025b20(void)

{
  undefined2 *unaff_A2;
  
  if ((DAT_00ff6189 & 0x10) != 0) {
    *unaff_A2 = DAT_00ff61a4;
    unaff_A2[1] = DAT_00ff61a6;
    unaff_A2[2] = 0x6a;
    if (7 < ((byte)DAT_00ff6010 & 0xf)) {
      unaff_A2[1] = unaff_A2[1] + -2;
    }
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

