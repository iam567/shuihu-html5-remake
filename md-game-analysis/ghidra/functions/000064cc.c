/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000064cc */

void FUN_000064cc(void)

{
  DAT_00ff618f = DAT_00ff618f | 8;
  FUN_00003354();
  DAT_00ff6038 = 3;
  DAT_00ff6039 = 0x20;
  return;
}

