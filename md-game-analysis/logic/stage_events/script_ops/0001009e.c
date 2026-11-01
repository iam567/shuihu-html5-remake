/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001009e */

void FUN_0001009e(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 unaff_A3;
  
  DAT_00ffe1f7 = 2;
  DAT_00ff6102 = 1;
  DAT_00ffe1e0 = 0;
  DAT_00ff6080 = 0x3fffffff;
  puVar2 = &DAT_00ffe780;
  sVar1 = 0xb;
  DAT_00ff6130 = unaff_A3;
  do {
    *(undefined1 *)((int)puVar2 + 1) = 0x10;
    *(undefined1 *)((int)puVar2 + 6) = 1;
    puVar2 = puVar2 + 0x10;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  puVar3 = &DAT_00ffea80;
  sVar1 = 0x11;
  do {
    puVar3[1] = 0x11;
    puVar3[6] = 1;
    puVar3 = puVar3 + 0x40;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}

