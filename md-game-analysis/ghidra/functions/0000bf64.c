/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000bf64 */

short FUN_0000bf64(void)

{
  short sVar1;
  ushort uVar2;
  
  uVar2 = (ushort)(byte)(DAT_00ff60b9 - 1);
  do {
    sVar1 = FUN_00006f50();
    uVar2 = uVar2 - 1;
  } while (uVar2 != 0xffff);
  return sVar1 + -1;
}

