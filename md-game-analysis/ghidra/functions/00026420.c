/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00026420 */

void FUN_00026420(void)

{
  short sVar1;
  short sVar2;
  short *unaff_A2;
  
  if (DAT_00ffe100 == 0x307) {
    sVar1 = -DAT_00ff6014 + 0xc0;
    if ((sVar1 < 0x141) && (-0x21 < sVar1)) {
      sVar2 = -DAT_00ff6016;
      sVar1 = sVar2 + 0x20;
      if ((sVar1 < 0xf1) && (-0x21 < sVar1)) {
        *unaff_A2 = -DAT_00ff6014 + 0x140;
        unaff_A2[1] = sVar2 + 0xa0;
        unaff_A2[2] = 0x8c;
        DAT_00ff6012 = DAT_00ff6012 + 1;
      }
    }
  }
  return;
}

