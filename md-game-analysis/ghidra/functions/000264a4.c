/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000264a4 */

void FUN_000264a4(void)

{
  undefined2 *unaff_A2;
  
  if (DAT_00ff61b1 != '\0') {
    DAT_00ff61b2 = DAT_00ff61b2 + 8;
    if (DAT_00ff61b2 < 0x161) {
      *unaff_A2 = 0x108;
      unaff_A2[1] = DAT_00ff61b2;
      unaff_A2[2] = 0x92;
      DAT_00ff6012 = DAT_00ff6012 + 1;
    }
    else {
      DAT_00ff61b1 = '\0';
      DAT_00ff603d = DAT_00ff603d | 2;
    }
  }
  return;
}

