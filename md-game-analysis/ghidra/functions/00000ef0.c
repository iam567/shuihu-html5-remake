/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00000ef0 */

void FUN_00000ef0(void)

{
  short sVar1;
  short extraout_D1w;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  
  do {
    sVar1 = 0x3f;
    puVar5 = &DAT_00ffef80;
    do {
      uVar2 = *puVar5 & 0xe00;
      if (uVar2 != 0) {
        uVar2 = uVar2 - 0x200;
      }
      uVar3 = *puVar5 & 0xe0;
      if (uVar3 != 0) {
        uVar3 = uVar3 - 0x20;
      }
      uVar4 = *puVar5 & 0xe;
      if (uVar4 != 0) {
        uVar4 = uVar4 - 2;
      }
      *puVar5 = uVar4 | uVar3 | uVar2;
      sVar1 = sVar1 + -1;
      puVar5 = puVar5 + 1;
    } while (sVar1 != -1);
    DAT_00ff6001 = 0xff;
    do {
      sVar1 = FUN_00000e40();
    } while (extraout_D1w != 0);
  } while (sVar1 != 0);
  return;
}

