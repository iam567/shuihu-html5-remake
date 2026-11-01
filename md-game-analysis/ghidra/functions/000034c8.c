/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000034c8 */

void FUN_000034c8(void)

{
  short sVar1;
  
  sVar1 = 6;
  do {
    FUN_00002e5a();
    FUN_00003142();
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}

