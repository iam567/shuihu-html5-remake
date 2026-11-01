/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000162b4 */

void FUN_000162b4(void)

{
  ushort extraout_D1w;
  short *unaff_A3;
  
  *unaff_A3 = unaff_A3[2] + *unaff_A3;
  unaff_A3[1] = unaff_A3[3] + unaff_A3[1];
  FUN_0001655c();
  *(char *)(unaff_A3 + 4) = (char)(extraout_D1w >> 7);
  return;
}

