/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00027ae8 */

void FUN_00027ae8(void)

{
  FUN_00000ef0();
  DAT_00400000 = DAT_00400002 + 'i';
  DAT_00ff601c = 0;
  FUN_000010ac();
  DAT_00ff600a = 0x120;
  DAT_00ff603a = 1;
  FUN_00003a82();
  Seed_e50();
  Seed_1028();
  Seed_1060();
  Seed_1060();
  Seed_1060();
  FUN_00002d38();
  FUN_00000e7c();
  DAT_00ff611a = 2;
  DAT_00ff610e = 7;
  DAT_00ff611b = 0;
  do {
    while( true ) {
      while( true ) {
        FUN_00000e40();
        if ((DAT_00ff6004 & 1) == 0) break;
        DAT_00ff611b = 0;
        FUN_00027f08();
        Seed_1060();
        Seed_1060();
      }
      if ((DAT_00ff6004 & 2) == 0) break;
      DAT_00ff611b = 1;
      FUN_00027f08();
      Seed_1060();
      Seed_1060();
    }
  } while ((DAT_00ff6004 & 0xf0) == 0);
  FUN_00027f18();
  DAT_00ff611a = 0;
  return;
}

