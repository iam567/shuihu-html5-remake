/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001f9fb0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_001f9fb0(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short extraout_D1w;
  short extraout_D1w_00;
  short sVar1;
  undefined2 unaff_D6w;
  char *pcVar2;
  char *extraout_A0;
  char *pcVar3;
  char *extraout_A1;
  
  _DAT_00ff0f94 = 0x51c0;
  _DAT_00fff050 = 0xe00f0b;
  DAT_00fff054 = 0x66d000e0;
  do {
    _DAT_00fff050 = CONCAT22(DAT_00fff050 + 0xff,DAT_00fff050_2);
    func_0x0000540e();
    func_0x0000a892();
  } while (extraout_D1w != 0);
  DAT_00fff050_2 = 0xf0b;
  DAT_00fff050 = 0xc0;
  DAT_00fff054 = 0x66d000e0;
  pcVar2 = "";
  pcVar3 = "";
  sVar1 = 2;
  do {
    do {
      DAT_00fff054 = CONCAT22(DAT_00fff054._0_2_,*pcVar2 + DAT_00fff054._2_2_);
      DAT_00fff050 = *pcVar3 + DAT_00fff050;
      func_0x0000540e();
      func_0x0000a892();
      pcVar2 = extraout_A0;
      pcVar3 = extraout_A1;
    } while (extraout_D1w_00 != 0);
    pcVar2 = "";
    pcVar3 = "";
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00fff054 = CONCAT22(0x66e0,DAT_00fff054._2_2_);
  _DAT_00ff0e28 = DAT_00fff054._2_2_;
  _DAT_00ff0e2c = DAT_00fff050;
  _DAT_00ff3d00 = 0x8048;
  FUN_001e41d4();
  DAT_00ff0e20 = 0;
  sVar1 = 0x7f;
  do {
    FUN_00000466();
    DAT_00fff050 = FUN_0000e074();
    DAT_00fff054 = CONCAT22(DAT_00fff054._0_2_,unaff_D6w);
    FUN_00000494();
    DAT_00ff0e20 = DAT_00ff0e20 + 1;
    if (0xc < DAT_00ff0e20) {
      DAT_00ff0e20 = 0;
      FUN_0002117e();
    }
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  _DAT_00ff3360 = 0x51c0;
  return CONCAT44(in_D0,in_D1);
}

