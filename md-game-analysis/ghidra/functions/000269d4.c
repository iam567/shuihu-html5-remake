/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000269d4 */

void FUN_000269d4(void)

{
  undefined2 *unaff_A2;
  
  if ((DAT_00ff6189 & 0x20) != 0) {
    *unaff_A2 = 0xa0;
    if (7 < ((byte)DAT_00ff6010 & 0xf)) {
      *unaff_A2 = 0x9c;
    }
    unaff_A2[1] = 200;
    if (DAT_00ff6174 != '\0') {
      unaff_A2[1] = 0x118;
    }
    unaff_A2[2] = 0x9b;
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

