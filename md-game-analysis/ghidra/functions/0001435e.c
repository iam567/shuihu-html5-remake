/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001435e */

void FUN_0001435e(void)

{
  DAT_00ff60c4 = *(undefined1 *)
                  ((int)&DAT_00ffe780 +
                  (int)(short)(ushort)(byte)(DAT_00ff60b7 + 0x26) +
                  (int)(short)((ushort)DAT_00ff606b << 6));
  DAT_00ff60ba = 3;
  if (*(char *)((int)&DAT_00ffe780 +
               (int)(short)(ushort)(byte)(DAT_00ff60b7 + 0x2b) +
               (int)(short)((ushort)DAT_00ff606b << 6)) == '\0') {
    DAT_00ff60ba = 4;
  }
  DAT_00ff60b9 = 2;
  FUN_0000bf64();
  DAT_00ff60ba = 3;
  FUN_0000bf64();
  FUN_0000bf64();
  FUN_0000bf64();
  return;
}

