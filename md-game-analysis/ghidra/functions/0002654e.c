/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0002654e */

void FUN_0002654e(void)

{
  short sVar1;
  short sVar2;
  short *unaff_A2;
  
  if (DAT_00ffe100 == 0xa06) {
    sVar1 = -DAT_00ff6014 + 0x2a8;
    if ((sVar1 < 0x141) && (-0x21 < sVar1)) {
      sVar2 = -DAT_00ff6016;
      sVar1 = sVar2 + 200;
      if ((sVar1 < 0xf1) && (-0x21 < sVar1)) {
        *unaff_A2 = -DAT_00ff6014 + 0x328;
        unaff_A2[1] = sVar2 + 0x148;
        unaff_A2[2] = 0x8e;
        DAT_00ff6012 = DAT_00ff6012 + 1;
      }
    }
  }
  return;
}

