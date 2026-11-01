/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001665a */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001665a(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  ushort extraout_D1w;
  ushort extraout_D1w_00;
  ushort uVar1;
  short sVar2;
  short sVar3;
  uint unaff_D2;
  ushort uVar4;
  short sVar5;
  short sVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  
  _DAT_00ff60c4 = DAT_00ff6302;
  FUN_0001655c();
  bVar8 = (unaff_D2 & 1) != 0;
  FUN_0001664e();
  bVar9 = (unaff_D2 & 1) != 0;
  uVar1 = DAT_00ff6306 - DAT_00ff630e;
  bVar7 = (short)uVar1 < 0;
  if (bVar7) {
    uVar1 = -uVar1;
  }
  sVar2 = (short)(((uint)uVar1 * (uint)extraout_D1w_00) / 10000);
  if (bVar7) {
    if (!bVar9) {
      sVar2 = -sVar2;
    }
  }
  else if (bVar9) {
    sVar2 = -sVar2;
  }
  uVar1 = -(DAT_00ff6304 - DAT_00ff630c);
  uVar4 = uVar1;
  if ((short)uVar1 < 0) {
    uVar4 = DAT_00ff6304 - DAT_00ff630c;
  }
  sVar5 = (short)(((uint)uVar4 * (uint)extraout_D1w) / 10000);
  if ((short)uVar1 < 0) {
    if (!bVar8) {
      sVar5 = -sVar5;
    }
  }
  else if (bVar8) {
    sVar5 = -sVar5;
  }
  uVar1 = DAT_00ff6304 - DAT_00ff630c;
  bVar7 = (short)uVar1 < 0;
  if (bVar7) {
    uVar1 = -uVar1;
  }
  sVar3 = (short)(((uint)uVar1 * (uint)extraout_D1w_00) / 10000);
  if (bVar7) {
    if (!bVar9) {
      sVar3 = -sVar3;
    }
  }
  else if (bVar9) {
    sVar3 = -sVar3;
  }
  uVar1 = DAT_00ff6306 - DAT_00ff630e;
  bVar7 = (short)uVar1 < 0;
  if (bVar7) {
    uVar1 = -uVar1;
  }
  sVar6 = (short)(((uint)uVar1 * (uint)extraout_D1w) / 10000);
  if (bVar7) {
    if (!bVar8) {
      sVar6 = -sVar6;
    }
  }
  else if (bVar8) {
    sVar6 = -sVar6;
  }
  DAT_00ff6308 = DAT_00ff630c + sVar6 + sVar3;
  DAT_00ff630a = DAT_00ff630e + sVar5 + sVar2;
  return CONCAT44(in_D0,in_D1);
}

