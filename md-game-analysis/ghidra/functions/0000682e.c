/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000682e */

void FUN_0000682e(void)

{
  byte bVar1;
  
  DAT_00ffe1f6 = DAT_00ffe10e;
  bVar1 = DAT_00ff606b;
  do {
    bVar1 = bVar1 + 1;
    if (0xb < bVar1) {
      bVar1 = 0;
    }
  } while ((*(char *)((int)&DAT_00ffe780 + (int)(short)((ushort)bVar1 << 6)) == '\0') ||
          (((DAT_00ffe1e0 & 1 << (bVar1 & 0x1f)) == 0 && (bVar1 != DAT_00ff606b))));
  DAT_00ff606b = bVar1;
  DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)bVar1 << 6) + 2) >> 5;
  DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)bVar1 << 6)) >> 5;
  DAT_00ff605a = 1;
  DAT_00ff6036 = 0;
  DAT_00ffe10e = 8;
  return;
}

