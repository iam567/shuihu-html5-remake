/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000150ee */

void FUN_000150ee(void)

{
  FUN_00006912();
  FUN_00001098();
  FUN_0000a596();
  FUN_00006c86();
  FUN_00015172();
  if (DAT_00ff7180 != 0xff) {
    DAT_00ff6087 = 0;
    DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff7180 << 6) + 2) >> 5;
    DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff7180 << 6)) >> 5;
    DAT_00ff605a = 1;
    DAT_00ff6036 = 0;
  }
  DAT_00ff6085 = 4;
  return;
}

