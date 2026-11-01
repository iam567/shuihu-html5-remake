/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001f9f02 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_001f9f02(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short extraout_D1w;
  
  do {
    DAT_00fff050 = DAT_00fff050 + 1;
    DAT_00fff05e = DAT_00fff05e + -1;
    DAT_00fff060 = DAT_00fff060 + -1;
    DAT_00fff06e = DAT_00fff06e + 1;
    func_0x0000540e();
    func_0x0000a892();
  } while (extraout_D1w != 0);
  _DAT_00ff3d00 = 0x807f;
  FUN_001e41d4();
  DAT_00fff058 = 0;
  DAT_00fff060 = 0;
  DAT_00fff068 = 0;
  FUN_00006560(0xff8000,&DAT_00039d20);
  func_0x000052fa(0x6d0,&DAT_00ff8200,0x200);
  FUN_000064cc(&DAT_00ffcf60,&DAT_00039d00,7);
  FUN_00000466();
  _DAT_00ff0f94 = &UNK_000fa120;
  return CONCAT44(in_D0,in_D1);
}

