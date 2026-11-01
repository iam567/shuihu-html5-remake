/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006452 */

void FUN_00006452(void)

{
  if (DAT_00ff6039 == '\0') {
    if (DAT_00ffe105 == DAT_00ff6051) {
      if (DAT_00ffe104 == DAT_00ff6050) {
        return;
      }
      if (DAT_00ffe104 < DAT_00ff6050) {
        DAT_00ffe104 = DAT_00ffe104 + '\x01';
        DAT_00ff618f = DAT_00ff618f | 8;
        FUN_00003354();
        DAT_00ff6038 = 3;
      }
      else {
        DAT_00ffe104 = DAT_00ffe104 + -1;
        DAT_00ff618f = DAT_00ff618f | 4;
        FUN_00003326();
        DAT_00ff6038 = 2;
      }
    }
    else if (DAT_00ffe105 < DAT_00ff6051) {
      DAT_00ffe105 = DAT_00ffe105 + '\x01';
      DAT_00ff618f = DAT_00ff618f | 2;
      FUN_000032f2();
      DAT_00ff6038 = 1;
    }
    else {
      DAT_00ffe105 = DAT_00ffe105 + -1;
      DAT_00ff618f = DAT_00ff618f | 1;
      FUN_000032c4();
      DAT_00ff6038 = 0;
    }
    DAT_00ff6039 = ' ';
  }
  return;
}

