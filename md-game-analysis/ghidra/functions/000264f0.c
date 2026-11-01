/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000264f0 */

void FUN_000264f0(void)

{
  short sVar1;
  short sVar2;
  short *unaff_A2;
  
  if (DAT_00ffe100 == 0x809) {
    sVar1 = -DAT_00ff6014 + 0x188;
    if ((sVar1 < 0x141) && (-0x21 < sVar1)) {
      sVar2 = -DAT_00ff6016;
      sVar1 = sVar2 + 0x1a0;
      if ((sVar1 < 0xf1) && (-0x21 < sVar1)) {
        *unaff_A2 = -DAT_00ff6014 + 0x208;
        unaff_A2[1] = sVar2 + 0x220;
        unaff_A2[2] = 0x93;
        DAT_00ff6012 = DAT_00ff6012 + 1;
      }
    }
  }
  return;
}

