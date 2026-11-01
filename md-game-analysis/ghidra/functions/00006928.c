/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006928 */

void FUN_00006928(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  sVar1 = 0x3ff;
  puVar2 = (undefined4 *)&DAT_00ff8000;
  puVar3 = (undefined4 *)&DAT_00ff9000;
  puVar4 = (undefined4 *)&DAT_00ffa000;
  puVar5 = (undefined4 *)&DAT_00ff1000;
  puVar6 = &DAT_00ff2000;
  puVar7 = &DAT_00ff3000;
  puVar8 = &DAT_00ff4000;
  do {
    *puVar2 = 0xffffffff;
    *puVar3 = 0xffffffff;
    *puVar4 = 0xffffffff;
    *puVar5 = 0xffffffff;
    *puVar6 = 0xffffffff;
    *puVar7 = 0xffffffff;
    *puVar8 = 0xffffffff;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  } while (sVar1 != -1);
  return;
}

