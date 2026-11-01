/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000278ee */

void FUN_000278ee(void)

{
  if (DAT_00ff61bf != '\0') {
    DAT_00ff61bf = '\0';
    Seed_1060();
    DAT_00ff6119 = 1;
    DAT_00ff601a = 0;
    DAT_00ff601b = 0x1f;
    DAT_00ff601c = 2;
    DAT_00ff611a = 2;
    DAT_00ff610e = 7;
  }
  return;
}

