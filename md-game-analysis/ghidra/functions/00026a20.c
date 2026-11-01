/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00026a20 */

void FUN_00026a20(void)

{
  uint uVar1;
  
  uVar1 = DAT_00ffe120 / 0xe10 & 0xffff;
  DAT_00ff6110 = (short)((DAT_00ffe120 % 0xe10) / 0x3c);
  DAT_00ff6112 = (short)(uVar1 / 0x3c);
  DAT_00ff6114 = (short)(uVar1 % 0x3c);
  return;
}

