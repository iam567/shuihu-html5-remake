/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000032c4 */

void FUN_000032c4(void)

{
  char cVar1;
  
  DAT_00ff6198 = DAT_00ff6034;
  DAT_00ff6199 = DAT_00ff6035;
  cVar1 = DAT_00ff6035 - 4;
  if (DAT_00ff6035 < 4) {
    cVar1 = DAT_00ff6035 + 0x1c;
  }
  DAT_00ff6035 = cVar1;
  return;
}

