/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000b98c */

undefined8 FUN_0000b98c(void)

{
  byte bVar1;
  undefined4 in_D0;
  short sVar2;
  undefined4 in_D1;
  byte bVar3;
  byte *unaff_A2;
  byte *pbVar4;
  byte *pbVar5;
  
  pbVar4 = &DAT_00ff5000;
  sVar2 = 0x1f;
  do {
    bVar1 = *unaff_A2;
    bVar3 = DAT_00ff60b6;
    if ((bVar1 & 0x40) != 0) {
      bVar3 = (byte)DAT_00ff60b4 | DAT_00ff60b6 & 0xf0;
    }
    if ((bVar1 & 0x80) != 0) {
      bVar3 = DAT_00ff60b4._0_1_ | bVar3 & 0xf;
    }
    *pbVar4 = bVar3;
    bVar3 = DAT_00ff60b6;
    if ((bVar1 & 0x10) != 0) {
      bVar3 = (byte)DAT_00ff60b4 | DAT_00ff60b6 & 0xf0;
    }
    if ((bVar1 & 0x20) != 0) {
      bVar3 = DAT_00ff60b4._0_1_ | bVar3 & 0xf;
    }
    pbVar4[1] = bVar3;
    bVar3 = DAT_00ff60b6;
    if ((bVar1 & 4) != 0) {
      bVar3 = (byte)DAT_00ff60b4 | DAT_00ff60b6 & 0xf0;
    }
    if ((bVar1 & 8) != 0) {
      bVar3 = DAT_00ff60b4._0_1_ | bVar3 & 0xf;
    }
    pbVar5 = pbVar4 + 3;
    pbVar4[2] = bVar3;
    bVar3 = DAT_00ff60b6;
    if ((bVar1 & 1) != 0) {
      bVar3 = (byte)DAT_00ff60b4 | DAT_00ff60b6 & 0xf0;
    }
    if ((bVar1 & 2) != 0) {
      bVar3 = DAT_00ff60b4._0_1_ | bVar3 & 0xf;
    }
    pbVar4 = pbVar4 + 4;
    *pbVar5 = bVar3;
    sVar2 = sVar2 + -1;
    unaff_A2 = unaff_A2 + 1;
  } while (sVar2 != -1);
  return CONCAT44(in_D0,in_D1);
}

