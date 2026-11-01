/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001fed46 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_001fed46(void)

{
  char cVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  short extraout_D1w;
  uint uVar2;
  ushort uVar3;
  uint extraout_D1;
  int iVar4;
  short sVar5;
  ushort uVar6;
  short sVar7;
  undefined *puVar8;
  int extraout_A0;
  short *psVar9;
  short *extraout_A0_00;
  
  func_0x0000635a(&DAT_000fef42 + (uint)DAT_00ff0f80 * 0x152,0x40000003,0xb,1,0x28);
  DAT_00ff0dfc = '!';
  DAT_00ff0dfd = '\x01';
  DAT_00ff0dfe = 2;
  DAT_00ff0e06 = 0;
  DAT_00ff0e00 = 0;
  DAT_00ff0e01 = 0;
  DAT_00ff0e48 = 0;
  _DAT_00ff0e10 = 0x4000;
  puVar8 = &DAT_000fff84;
  sVar7 = 0x500;
  cVar1 = DAT_00ff0dfd;
  do {
    DAT_00ff0dfd = cVar1;
    FUN_00006a08(0x40000003,sVar7,puVar8);
    sVar7 = sVar7 + 0x10;
    puVar8 = (undefined *)(extraout_A0 + 6);
    cVar1 = DAT_00ff0dfd + '\x03';
  } while (extraout_D1w != 0);
  DAT_00ff0dfc = DAT_00ff0dfc + '\v';
  DAT_00ff0dfd = DAT_00ff0dfd + '\x04';
  DAT_00ff0dfe = 9;
  FUN_00006a08(0x40000003,sVar7,*(undefined4 *)(&DAT_0003992a + (short)((ushort)DAT_00ff0f80 << 2)))
  ;
  func_0x0000540e();
  func_0x00007cb2();
  iVar4 = 0x74000003;
  FUN_00006520(0xff8000,0,0x3f);
  psVar9 = (short *)&DAT_00ff8000;
  sVar5 = 0x100;
  uVar2 = 0;
  uVar6 = 0;
  sVar7 = 0;
  do {
    do {
      DAT_00ff0f4e = DAT_00ff0f4e & 0xdf;
      Ram00c00004 = iVar4;
      if (*psVar9 != -0x100) {
        *psVar9 = *psVar9 + -8;
        Ram00c00000 = *psVar9;
      }
      DAT_00ff0f4e = DAT_00ff0f4e | 0x20;
      iVar4 = iVar4 + 0x40000;
      psVar9 = psVar9 + 1;
      uVar3 = (short)uVar2 - 1;
      uVar2 = (uint)uVar3;
    } while (uVar3 != 0xffff);
    iVar4 = 0x74000003;
    if (DAT_00fff008._0_2_ != 0x120) {
      DAT_00fff008._0_2_ = DAT_00fff008._0_2_ + 1;
      uVar6 = uVar6 + 1;
      if ((7 < uVar6) && (uVar6 = 0, sVar7 < 5)) {
        FUN_00021090();
        sVar7 = sVar7 + 1;
      }
    }
    FUN_00000466();
    if (((byte)DAT_00ff0000 & 0x40) != 0) {
      DAT_00ff0fca = DAT_00ff0fca | 1;
      sVar5 = 0;
    }
    FUN_00000494();
    sVar5 = sVar5 + -1;
    uVar2 = extraout_D1;
    psVar9 = extraout_A0_00;
  } while (sVar5 != -1);
  func_0x00005920(0);
  func_0x0000540e();
  func_0x00007cb2();
  Ram00c00004 = 0x8b00;
  func_0x00005534();
  return CONCAT44(in_D0,in_D1);
}

