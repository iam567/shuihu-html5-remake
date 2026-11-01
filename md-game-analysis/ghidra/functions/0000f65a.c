/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000f65a */

void FUN_0000f65a(void)

{
  ushort unaff_D6w;
  ushort unaff_D7w;
  
  DAT_00ff6124 = 0xc500;
  FUN_0000f772();
  FUN_0000f7c8();
  if (1 < unaff_D6w) {
    DAT_00ff6124 = 0xc501;
    FUN_0000f772();
  }
  FUN_0000f7c8();
  DAT_00ff6124 = 0xcd00;
  FUN_0000f772();
  FUN_0000f7d6();
  if (1 < unaff_D7w) {
    DAT_00ff6124 = 0xc502;
    FUN_0000f772();
    FUN_0000f7c8();
    if (1 < unaff_D6w) {
      DAT_00ff6124 = 0xc503;
      FUN_0000f772();
    }
    FUN_0000f7c8();
    DAT_00ff6124 = 0xcd02;
    FUN_0000f772();
  }
  FUN_0000f7d6();
  DAT_00ff6124 = 0xd500;
  FUN_0000f772();
  FUN_0000f7c8();
  if (1 < unaff_D6w) {
    DAT_00ff6124 = 0xd501;
    FUN_0000f772();
  }
  FUN_0000f7c8();
  DAT_00ff6124 = 0xdd00;
  FUN_0000f772();
  return;
}

