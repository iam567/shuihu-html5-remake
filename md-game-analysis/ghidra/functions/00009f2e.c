/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009f2e */

void FUN_00009f2e(void)

{
  uint uVar1;
  short sVar2;
  
  if (DAT_00ff609a != '\0') {
    FUN_00006f50();
    uVar1 = ((uint)DAT_00ff608e * 0x60) / (uint)DAT_00ff6090 & 0xffff;
    sVar2 = (short)(uVar1 / 8);
    if (sVar2 != 0) {
      sVar2 = sVar2 + -1;
      do {
        FUN_00006f50();
        sVar2 = sVar2 + -1;
      } while (sVar2 != -1);
    }
    if ((short)(uVar1 % 8) != 0) {
      FUN_00006f50();
    }
    DAT_00ff60ac = 3;
    FUN_0000b3ec();
    FUN_00006f50();
    uVar1 = ((uint)DAT_00ff6094 * 0x60) / (uint)DAT_00ff6096 & 0xffff;
    sVar2 = (short)(uVar1 / 8);
    if (sVar2 != 0) {
      sVar2 = sVar2 + -1;
      do {
        FUN_00006f50();
        sVar2 = sVar2 + -1;
      } while (sVar2 != -1);
    }
    if ((short)(uVar1 % 8) != 0) {
      FUN_00006f50();
    }
    DAT_00ff60ac = 3;
    FUN_0000b3ec();
  }
  return;
}

