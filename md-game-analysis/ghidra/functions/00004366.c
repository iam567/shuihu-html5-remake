/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00004366 */

void FUN_00004366(void)

{
  short sVar1;
  short *unaff_A2;
  
  if (DAT_00ff6120 != '\0') {
    DAT_00ff6048 = (DAT_00ffe1f0 - DAT_00ff6014) + 0x80;
    sVar1 = (DAT_00ffe1f2 - DAT_00ff6016) + 0x80;
    DAT_00ff604a = sVar1;
    *unaff_A2 = DAT_00ff6048;
    unaff_A2[1] = sVar1;
    unaff_A2[2] = 0x3d;
    if (7 < ((byte)DAT_00ff6010 & 0xf)) {
      unaff_A2[2] = 0x3e;
    }
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

