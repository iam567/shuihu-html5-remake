/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001fadec */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_001fadec(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short extraout_D1w;
  short sVar1;
  int extraout_A0;
  
  if ((DAT_00ff32c5 & 1) == 0) {
    _DAT_00ff32c6 = &UNK_000fae78;
    FUN_00012fbc();
    sVar1 = 1;
    do {
      do {
        DAT_00fff058 = DAT_00fff058 + 0x100;
        func_0x0000540e();
        func_0x0000a892();
      } while (extraout_D1w != 0);
      *(undefined **)(extraout_A0 + 6) = &DAT_0008defa;
      *(undefined **)(extraout_A0 + 10) = &DAT_000381f8;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    DAT_00ff32c5 = DAT_00ff32c5 | 1;
    func_0x00008358(0x14);
    _DAT_00ff32c6 = &UNK_000faeaa;
    FUN_00012fbc();
  }
  return CONCAT44(in_D0,in_D1);
}

