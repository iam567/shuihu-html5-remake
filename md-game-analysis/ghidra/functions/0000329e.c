/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000329e */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0000329e(void)

{
  short extraout_D1w;
  
  FUN_00003284();
  _DAT_00ff6028 = extraout_D1w;
  DAT_00ff6032 = (&DAT_00ffd000)[extraout_D1w];
  return;
}

