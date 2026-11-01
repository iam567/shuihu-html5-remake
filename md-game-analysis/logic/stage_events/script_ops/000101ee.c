/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000101ee */

void FUN_000101ee(void)

{
  undefined2 *unaff_A3;
  
  DAT_00ff6130 = unaff_A3 + 1;
  *(char *)((int)&DAT_00ffe780 + (int)(short)((ushort)DAT_00ff613e << 6)) = (char)*unaff_A3;
  DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff613e & 0x1f);
  return;
}

