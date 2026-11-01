/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000010c8 */

void FUN_000010c8(void)

{
  short sVar1;
  undefined4 *puVar2;
  
  DAT_00ff6002 = 0xff;
  sVar1 = 0x9f;
  puVar2 = (undefined4 *)&DAT_00fff000;
  do {
    *puVar2 = 0;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (sVar1 != -1);
  return;
}

