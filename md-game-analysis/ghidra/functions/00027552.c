/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00027552 */

void FUN_00027552(void)

{
  if ((DAT_00ff6116 != '\0') && ((DAT_00ff6010 & 0xf) == 0)) {
    Seed_1060();
    DAT_00ff6116 = DAT_00ff6116 + '\x01';
    if (DAT_00ff6116 < '9') {
      DAT_00ff605c._1_1_ = (char)DAT_00ff605c + '\x03';
      if ('\x17' < (char)DAT_00ff605c) {
        DAT_00ff605c._1_1_ = '\x03';
        DAT_00ff605c._0_1_ = DAT_00ff605c._0_1_ + -4;
      }
    }
    else {
      DAT_00ff6116 = '\0';
      DAT_00ff6117 = 1;
    }
  }
  return;
}

