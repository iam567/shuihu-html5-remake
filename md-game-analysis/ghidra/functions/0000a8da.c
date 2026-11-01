/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000a8da */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0000a8da(void)

{
  ushort uVar1;
  byte unaff_D2b;
  
  if ((((DAT_00ff60a9 == '\x02') && ((DAT_00ff603d & 1) == 0)) && (DAT_00ff604c == '\0')) &&
     ((DAT_00ff6159 == '\0' && (FUN_00006200(), unaff_D2b < 0x1e)))) {
    DAT_00ff60a9 = '\0';
    DAT_00ff60c8._0_1_ = unaff_D2b;
    Seed_e50();
    DAT_00ff60c0._0_2_ = (ushort)(DAT_00ffe1f0 - DAT_00ff6014) >> 3;
    uVar1 = (ushort)(DAT_00ffe1f2 - DAT_00ff6016) >> 3;
    DAT_00ff60d0._0_1_ = 0x14 < DAT_00ff60c0._0_2_;
    if ((bool)DAT_00ff60d0._0_1_) {
      DAT_00ff60c0._0_2_ = DAT_00ff60c0._0_2_ - 0xe;
    }
    if (uVar1 < 9) {
      _DAT_00ff60c4 = uVar1 + 5;
      DAT_00ff60d0._0_1_ = DAT_00ff60d0._0_1_ | 2;
    }
    else {
      _DAT_00ff60c4 = uVar1 - 7;
    }
    FUN_00006f50();
    FUN_00006f50();
    FUN_000144f8();
    FUN_0000adb6();
    FUN_0000ace2();
  }
  return;
}

