/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000ec60 */

void FUN_0000ec60(void)

{
  if (DAT_00ff611d != '\0') {
    if (DAT_00ff611d == '\x01') {
      Seed_e50();
      FUN_00006f50();
      DAT_00ff611d = '\x02';
    }
    else if (DAT_00ff611d == -0x7e) {
      DAT_00ff611d = '\0';
    }
    else {
      DAT_00ff600a = *(short *)((int)&PTR_DAT_0000ecf0 +
                               (int)(short)((ushort)(byte)(DAT_00ff611d - 2) << 1)) + DAT_00ff600a;
      DAT_00ff603a = 1;
      DAT_00ff611d = DAT_00ff611d + '\x01';
    }
  }
  return;
}

