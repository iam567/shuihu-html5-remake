/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006f50 */

undefined8 FUN_00006f50(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short unaff_D2w;
  short unaff_D3w;
  short sVar1;
  
  sVar1 = unaff_D2w;
  do {
    do {
      FUN_00006fa2();
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    unaff_D3w = unaff_D3w + -1;
    sVar1 = unaff_D2w;
  } while (unaff_D3w != -1);
  return CONCAT44(in_D0,in_D1);
}

