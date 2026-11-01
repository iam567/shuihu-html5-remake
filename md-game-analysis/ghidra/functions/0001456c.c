/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001456c */

void FUN_0001456c(void)

{
  uint uVar1;
  short sVar2;
  short sVar3;
  short *unaff_A2;
  
  if (DAT_00ff6140 == '\0') {
    return;
  }
  uVar1 = (uint)DAT_00ff6128 % 0x30;
  if (uVar1 == 0) {
LAB_000145d8:
    sVar2 = 0x148;
    sVar3 = 0x118;
    if ((DAT_00ff6141 & 1) != 0) {
      sVar2 = 0xb8;
    }
  }
  else {
    sVar3 = (short)(uVar1 / 0x10);
    if (0x30 < DAT_00ff6128) {
      if ((DAT_00ff6128 & 0xf) == 0) goto LAB_000145d8;
      sVar3 = (short)CONCAT31((uint3)(byte)(DAT_00ff6128 >> 8),2);
    }
    sVar2 = sVar3 * 0x10 + 0x120;
    if ((DAT_00ff6141 & 1) != 0) {
      sVar2 = sVar3 * 0x10 + 0x90;
    }
    sVar3 = (short)(uVar1 % 0x10) * 0x10 + 0xa0;
  }
  *unaff_A2 = sVar3;
  unaff_A2[1] = sVar2;
  unaff_A2[2] = 0x45;
  if (7 < ((byte)DAT_00ff6010 & 0xf)) {
    unaff_A2[2] = 0x46;
  }
  DAT_00ff6012 = DAT_00ff6012 + 1;
  return;
}

