/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000eb74 */

void FUN_0000eb74(void)

{
  ushort uVar1;
  
  DAT_00ff609a = DAT_00ff609a + -1;
  if (DAT_00ff609a == '\0') {
    DAT_00ff60aa = 0;
    FUN_00001098();
    DAT_00ff6085 = 0;
    DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
    uVar1 = (ushort)DAT_00ff606b;
    *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar1 << 6) + 1) = 0x10;
    *(undefined1 *)((int)&DAT_00ffe784 + (short)(uVar1 << 6) + 2) = 1;
  }
  return;
}

