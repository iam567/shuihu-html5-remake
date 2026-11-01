/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003354 */

void FUN_00003354(void)

{
  DAT_00ff6198 = DAT_00ff6034;
  DAT_00ff6199 = DAT_00ff6035;
  DAT_00ff6034 = DAT_00ff6034 + 4;
  if (0x3e < DAT_00ff6034) {
    DAT_00ff6034 = 0;
  }
  return;
}

