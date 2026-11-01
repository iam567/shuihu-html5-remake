/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00000e7c */

void FUN_00000e7c(void)

{
  short sVar1;
  short extraout_D1w;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  ushort *puVar6;
  
  do {
    sVar1 = 0x3f;
    puVar5 = &DAT_00ffef00;
    puVar6 = &DAT_00ffef80;
    do {
      uVar2 = *puVar6 & 0xe00;
      if (uVar2 < (*puVar5 & 0xe00)) {
        uVar2 = uVar2 + 0x200;
      }
      uVar3 = *puVar6 & 0xe0;
      if (uVar3 < (*puVar5 & 0xe0)) {
        uVar3 = uVar3 + 0x20;
      }
      uVar4 = *puVar6 & 0xe;
      if (uVar4 < (*puVar5 & 0xe)) {
        uVar4 = uVar4 + 2;
      }
      *puVar6 = uVar4 | uVar3 | uVar2;
      sVar1 = sVar1 + -1;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    } while (sVar1 != -1);
    DAT_00ff6001 = 0xff;
    do {
      sVar1 = FUN_00000e40();
    } while (extraout_D1w != 0);
  } while (sVar1 != 0);
  return;
}

