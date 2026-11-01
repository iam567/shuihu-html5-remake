/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000063f8 */

void FUN_000063f8(void)

{
  if (DAT_00ff604f != '\0') {
    if ((DAT_00ffe104 == DAT_00ff6050) && (DAT_00ffe105 == DAT_00ff6051)) {
      if ((DAT_00ff6039 == '\0') && (DAT_00ff604f = '\0', DAT_00ff6043 == '\0')) {
        DAT_00ff603d = DAT_00ff603d | 2;
      }
    }
    else {
      FUN_00006452();
    }
  }
  return;
}

