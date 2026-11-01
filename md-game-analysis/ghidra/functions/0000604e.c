/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000604e */

undefined4 FUN_0000604e(void)

{
  undefined4 in_D0;
  
  DAT_00ff6100 = (short)(((uint)DAT_00ff6100 * 0x7fcf + 3) % 0x7fed);
  return in_D0;
}

