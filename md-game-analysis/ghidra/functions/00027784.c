/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00027784 */

void FUN_00027784(void)

{
  if (((DAT_00ff6010 & 1) == 0) && (DAT_00ff61be != '\0')) {
    DAT_00ff61be = '\0';
    FUN_000010ac();
    FUN_000010e0();
    FUN_00000e40();
    Seed_e50();
    Seed_1060();
    DAT_00ff6118 = 1;
    DAT_00ff601a = 0;
    DAT_00ff601b = 0x1f;
    DAT_00ff601c = 10;
  }
  return;
}

