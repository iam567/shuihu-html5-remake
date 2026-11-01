/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00027fb8 */

void FUN_00027fb8(void)

{
  short sVar1;
  undefined3 uVar2;
  undefined1 *puVar3;
  
  uVar2 = CONCAT21(CONCAT11(DAT_00200001,DAT_00200003),DAT_00200005);
  if (((CONCAT31(uVar2,DAT_00200007) != 0x6090108) &&
      (uVar2 = (undefined3)
               CONCAT31((int3)CONCAT31((int3)CONCAT31(uVar2,DAT_00202001),DAT_00202003),DAT_00202005
                       ), CONCAT31(uVar2,DAT_00202007) != 0x6090108)) &&
     (CONCAT31((int3)CONCAT31((int3)CONCAT31((int3)CONCAT31(uVar2,DAT_00203001),DAT_00203003),
                              DAT_00203005),DAT_00203007) != 0x6090108)) {
    puVar3 = &DAT_00200001;
    sVar1 = 0x1fff;
    do {
      *puVar3 = 0;
      puVar3 = puVar3 + 2;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
  }
  return;
}

