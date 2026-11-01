/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001ba3c */

void FUN_0001ba3c(void)

{
  undefined2 uVar1;
  undefined2 *unaff_A2;
  
  if ((DAT_00ff6189 & 4) != 0) {
    if (DAT_00ff617f != '\0') {
      *unaff_A2 = 200;
      uVar1 = 0xb1;
      if (7 < ((byte)DAT_00ff6010 & 0xf)) {
        uVar1 = 0xb3;
      }
      unaff_A2[1] = uVar1;
      unaff_A2[2] = 0x5e;
      unaff_A2 = unaff_A2 + 3;
      DAT_00ff6012 = DAT_00ff6012 + 1;
    }
    if ((7 < DAT_00ff618a) && ((byte)(DAT_00ff618a - 7) != DAT_00ff617f)) {
      *unaff_A2 = 200;
      uVar1 = 0x12e;
      if (7 < ((byte)DAT_00ff6010 & 0xf)) {
        uVar1 = 0x130;
      }
      unaff_A2[1] = uVar1;
      unaff_A2[2] = 0x5f;
      DAT_00ff6012 = DAT_00ff6012 + 1;
    }
  }
  return;
}

