/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00019d56 */

void FUN_00019d56(void)

{
  undefined2 *unaff_A2;
  
  if (DAT_00ff617e != '\0') {
    if (DAT_00ff617e == '\x01') {
      if (0x140 < DAT_00ff617c) {
        DAT_00ff617c = DAT_00ff617c - 8;
      }
    }
    else {
      if (0x16f < (short)DAT_00ff617c) {
        DAT_00ff617e = 0;
        return;
      }
      DAT_00ff617c = DAT_00ff617c + 8;
    }
    *unaff_A2 = 0x90;
    unaff_A2[1] = DAT_00ff617c;
    unaff_A2[2] = 0x5d;
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

