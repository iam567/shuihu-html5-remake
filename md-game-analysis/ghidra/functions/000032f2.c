/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000032f2 */

void FUN_000032f2(void)

{
  DAT_00ff6198 = DAT_00ff6034;
  DAT_00ff6199 = DAT_00ff6035;
  DAT_00ff6035 = DAT_00ff6035 + 4;
  if (0x1e < DAT_00ff6035) {
    DAT_00ff6035 = 0;
  }
  return;
}

