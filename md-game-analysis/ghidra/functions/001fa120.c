/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001fa120 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_001fa120(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  DAT_00ff0f82 = DAT_00ff0f82 + 1;
  _DAT_00fff050 = 0xe8050b;
  DAT_00fff054 = 0x66f000e8;
  if ((DAT_00ff0f82 & 1) != 0) {
    _DAT_00fff050 = 0xe00f0b;
    DAT_00fff054 = 0x66d000e0;
  }
  FUN_00000494();
  return CONCAT44(in_D0,in_D1);
}

