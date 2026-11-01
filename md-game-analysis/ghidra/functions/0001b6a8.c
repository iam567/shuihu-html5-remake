/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001b6a8 */

void FUN_0001b6a8(void)

{
  undefined2 *unaff_A2;
  
  if ((DAT_00ff6189 & 2) != 0) {
    *unaff_A2 = 0x88;
    unaff_A2[1] = DAT_00ff6178;
    unaff_A2[2] = 0x5b;
    if (7 < ((byte)DAT_00ff6010 & 0xf)) {
      unaff_A2[2] = 0x5c;
    }
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

