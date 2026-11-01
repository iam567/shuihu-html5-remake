/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000f20a */

void FUN_0000f20a(void)

{
  if (DAT_00ff6122 != '\0') {
    if (DAT_00ff6122 < '\t') {
      FUN_0000f65a();
      DAT_00ff6122 = DAT_00ff6122 + '\x01';
    }
    else {
      DAT_00ff6122 = '\0';
      FUN_00006f50();
      FUN_0001461e();
      DAT_00ff6126 = 1;
    }
  }
  return;
}

