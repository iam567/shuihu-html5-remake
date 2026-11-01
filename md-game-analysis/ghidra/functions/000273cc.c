/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000273cc */

void FUN_000273cc(void)

{
  do {
    FUN_00000ef0();
    DAT_00ffe116 = 0xff;
    FUN_000010ac();
    DAT_00ff600a = 0;
    DAT_00ff603a = 1;
    FUN_00003a82();
    Seed_e50();
    Seed_1028();
    FUN_00002d38();
    FUN_00000e7c();
    DAT_00ff605c._0_1_ = 0x20;
    DAT_00ff605c._1_1_ = 3;
    DAT_00ff6116 = 1;
    DAT_00ff611a = 1;
    DAT_00ff610d = 3;
    do {
      FUN_00000e40();
      if ((DAT_00ff6004 & 0xf0) != 0) {
        DAT_00ff61bc = 0;
        FUN_000010c8();
        return;
      }
      FUN_00027836();
      FUN_00027950();
      FUN_0002776a();
      FUN_00027784();
      FUN_000278ee();
      FUN_00027552();
      FUN_000274ec();
      FUN_00003a82();
    } while ((DAT_00ff6044 == 0) || (DAT_00ff6044 = DAT_00ff6044 + 1, DAT_00ff6044 < 0x259));
    DAT_00ff6044 = 0;
    DAT_00ff611a = 0;
    DAT_00ff61bc = 0;
    FUN_000010c8();
  } while( true );
}

