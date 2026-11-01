/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00000d92 */

void FUN_00000d92(void)

{
  undefined4 unaff_A3;
  
  if (((0x50 < DAT_00ff603c) && (DAT_00ff603c < 0x80)) && ((DAT_00ff603d & 1) == 0)) {
    DAT_00ff6036 = 0;
    DAT_00ff6138 = DAT_00ff603c;
    DAT_00ff6182 = DAT_00ffe100;
    DAT_00ff603d = DAT_00ff603d | 3;
    FUN_0001201a();
    DAT_00ffe1f6 = DAT_00ffe10e;
    DAT_00ff6130 = unaff_A3;
  }
  return;
}

