/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000260e8 */

void FUN_000260e8(void)

{
  short sVar1;
  short *unaff_A2;
  
  if (DAT_00ff61ae != 0) {
    *unaff_A2 = (DAT_00ffe1f0 + 0x80) - DAT_00ff6014;
    unaff_A2[1] = (DAT_00ffe1f2 + 0x80) - DAT_00ff6016;
    sVar1 = 0x77;
    if ((((8 < DAT_00ff61ae) && (sVar1 = 0x78, 0x10 < DAT_00ff61ae)) &&
        (sVar1 = 0x79, 0x18 < DAT_00ff61ae)) && (sVar1 = 0x7a, 0x20 < DAT_00ff61ae)) {
      sVar1 = 0x7b;
    }
    unaff_A2[2] = sVar1;
    DAT_00ff6012 = DAT_00ff6012 + 1;
    DAT_00ff61ae = DAT_00ff61ae + 1;
    if (0x28 < DAT_00ff61ae) {
      DAT_00ff61ae = 0;
      DAT_00ff603d = DAT_00ff603d | 2;
    }
  }
  return;
}

