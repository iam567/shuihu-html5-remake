/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00026f92 */

void FUN_00026f92(void)

{
  undefined2 *unaff_A2;
  
  if ((DAT_00ff6189 & 0x40) != 0) {
    *unaff_A2 = 0xa0;
    if (7 < ((byte)DAT_00ff6010 & 0xf)) {
      *unaff_A2 = 0x9c;
    }
    unaff_A2[1] = 0xb0;
    if ((DAT_00ff61af != '\0') && (unaff_A2[1] = 0xf0, DAT_00ff61af != '\x01')) {
      unaff_A2[1] = 0x130;
    }
    unaff_A2[2] = 0x9b;
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

