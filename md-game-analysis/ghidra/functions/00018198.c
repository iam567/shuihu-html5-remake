/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00018198 */

undefined8 FUN_00018198(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  uint uVar2;
  short sVar3;
  uint unaff_D3;
  short *psVar4;
  short *psVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  sVar1 = 0x1f;
  puVar6 = (undefined4 *)&DAT_00ffe080;
  do {
    *puVar6 = 0;
    sVar1 = sVar1 + -1;
    puVar6 = puVar6 + 1;
  } while (sVar1 != -1);
  DAT_00ff615e = 0xffff;
  puVar6 = &DAT_00ffe2c0;
  psVar4 = &DAT_00018232;
  while (psVar5 = psVar4, *psVar4 != -1) {
    psVar5 = psVar4 + 1;
    if (*psVar4 == DAT_00ffe100) {
      DAT_00ff615e = *(undefined2 *)puVar6;
      break;
    }
    puVar6 = (undefined4 *)((int)puVar6 + 2);
    psVar4 = psVar5;
  }
  FUN_00018252();
  puVar6 = (undefined4 *)&DAT_00ffe080;
  sVar1 = 0xf;
  uVar2 = 0;
  do {
    if (*(char *)psVar5 == '\0') break;
    unaff_D3 = CONCAT22((short)(unaff_D3 >> 0x10),DAT_00ff615e);
    if ((unaff_D3 & 1 << (uVar2 & 0x1f)) == 0) {
      psVar5 = psVar5 + 8;
    }
    else {
      sVar3 = 3;
      psVar4 = psVar5;
      puVar7 = puVar6;
      do {
        psVar5 = psVar4 + 2;
        puVar6 = puVar7 + 1;
        *puVar7 = *(undefined4 *)psVar4;
        sVar3 = sVar3 + -1;
        psVar4 = psVar5;
        puVar7 = puVar6;
      } while (sVar3 != -1);
    }
    uVar2 = (uint)(byte)((char)uVar2 + 1);
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00ff601e._0_1_ = 0xff;
  return CONCAT44(in_D0,in_D1);
}

