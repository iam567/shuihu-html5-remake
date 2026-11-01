/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00014144 */

void FUN_00014144(void)

{
  undefined1 unaff_D2b;
  undefined4 unaff_A3;
  
  DAT_00ff6182 = DAT_00ffe100;
  DAT_00ff6138 = unaff_D2b;
  FUN_0001201a();
  DAT_00ff6130 = unaff_A3;
  DAT_00ff603d = DAT_00ff603d | 3;
  DAT_00ff6036 = 0;
  DAT_00ffe1f6 = DAT_00ffe10e;
  return;
}

