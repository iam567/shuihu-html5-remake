/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000cfdc */

void FUN_0000cfdc(void)

{
  if (DAT_00ff6109 != '\0') {
    if (DAT_00ff610a == 0) {
      DAT_00ff6109 = '\0';
    }
    else {
      DAT_00ff610a = DAT_00ff610a - 1;
      DAT_00ff60c8 = (ushort)*(byte *)((int)&PTR_DAT_0000d036 +
                                      (int)(short)(ushort)(DAT_00ff610a >> 3) +
                                      (int)(short)((ushort)(byte)(DAT_00ff6109 - 1) << 3) +
                                      (int)(short)((ushort)(byte)(DAT_00ff6109 - 1) << 2));
      FUN_0000ca16();
    }
  }
  return;
}

