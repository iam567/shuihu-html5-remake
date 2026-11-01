/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000265ac */

void FUN_000265ac(void)

{
  undefined2 *unaff_A2;
  
  if (DAT_00ff6084 != 0) {
    if (DAT_00ff6084 < 0x41) {
      *unaff_A2 = 0x120;
      DAT_00ff6196 = *(short *)(&DAT_0002662c + (short)(DAT_00ff6084 - 1 & 0xfffe)) + DAT_00ff6196;
      unaff_A2[1] = DAT_00ff6196;
      unaff_A2[2] = 0x97;
      if (0x11 < DAT_00ff6084) {
        unaff_A2[2] = 0x98;
      }
      DAT_00ff6012 = DAT_00ff6012 + 1;
      DAT_00ff6084 = DAT_00ff6084 + 1;
    }
    else {
      DAT_00ff6084 = 0;
      DAT_00ff603d = DAT_00ff603d | 2;
    }
  }
  return;
}

