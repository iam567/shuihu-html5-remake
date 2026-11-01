/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000ace2 */

void FUN_0000ace2(void)

{
  int iVar1;
  
  iVar1 = (int)(short)((ushort)DAT_00ff60c8._0_1_ << 6);
  if (*(char *)((int)&DAT_00ffe78c + iVar1) != '\0') {
    FUN_00006f50();
  }
  if (*(char *)((int)&DAT_00ffe78c + iVar1 + 1) != '\0') {
    FUN_00006f50();
  }
  if (*(char *)((int)&DAT_00ffe78c + iVar1 + 2) != '\0') {
    FUN_00006f50();
  }
  if (*(char *)((int)&DAT_00ffe78c + iVar1 + 3) != '\0') {
    FUN_00006f50();
  }
  return;
}

