/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003326 */

void FUN_00003326(void)

{
  bool bVar1;
  
  DAT_00ff6198 = DAT_00ff6034;
  DAT_00ff6199 = DAT_00ff6035;
  bVar1 = DAT_00ff6034 < 4;
  DAT_00ff6034 = DAT_00ff6034 - 4;
  if (bVar1) {
    DAT_00ff6034 = '<';
  }
  return;
}

