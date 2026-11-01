/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e4be8 */

void FUN_001e4be8(void)

{
  (*(code *)(&DAT_001e4bfc + *(short *)(&DAT_001e4bfc + (short)((ushort)DAT_00ff6d04 * 2))))();
  return;
}

