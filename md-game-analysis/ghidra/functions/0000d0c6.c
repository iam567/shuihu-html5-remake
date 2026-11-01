/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d0c6 */

void FUN_0000d0c6(void)

{
  int iVar1;
  undefined1 extraout_var;
  
  FUN_00006912();
  FUN_00001098();
  FUN_0000d34a();
  FUN_00006c86();
  FUN_0000d148();
  if (DAT_00ff7180 != -1) {
    DAT_00ff6087 = 0;
    iVar1 = (int)(short)(CONCAT11(extraout_var,DAT_00ff7180) << 6);
    DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + iVar1 + 2) >> 5;
    DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + iVar1) >> 5;
    DAT_00ff605a = 1;
    DAT_00ff6036 = 0;
  }
  DAT_00ff6085 = 4;
  return;
}

