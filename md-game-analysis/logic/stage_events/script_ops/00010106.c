/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00010106 */

void FUN_00010106(void)

{
  undefined4 unaff_A3;
  
  DAT_00ff6130 = unaff_A3;
  DAT_00ff6019 = DAT_00ff6019 | 4;
  DAT_00ff603d = DAT_00ff603d & 0xfd;
  return;
}

