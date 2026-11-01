/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00000466 */

void FUN_00000466(void)

{
  undefined2 in_D1w;
  int unaff_A3;
  
  *(undefined2 *)(unaff_A3 + 2) = *(undefined2 *)(unaff_A3 + 4);
  *(undefined2 *)(unaff_A3 + 4) = in_D1w;
  DAT_00ff6001 = 0xff;
  return;
}

