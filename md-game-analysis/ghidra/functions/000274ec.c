/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000274ec */

void FUN_000274ec(void)

{
  if (DAT_00ff6117 != 0) {
    if (DAT_00ff6117 < 0xc1) {
      DAT_00ff6117 = DAT_00ff6117 + 1;
    }
    else if ((DAT_00ff6010 & 1) == 0) {
      if (DAT_00ff600a == 0x120) {
        DAT_00ff6117 = 0;
        DAT_00ff61bc = 1;
        FUN_000276cc();
      }
      else {
        DAT_00ff600a = DAT_00ff600a + 1;
        DAT_00ff603a = 1;
      }
    }
  }
  return;
}

