/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003c78 */

void FUN_00003c78(void)

{
  int unaff_A2;
  
  if (DAT_00ffe10d == '\x01') {
    if (((byte)DAT_00ff6010 & 0x3f) < 0x20) {
      return;
    }
  }
  else if (((byte)DAT_00ff6010 & 0x1f) < 0x10) {
    return;
  }
  *(char *)(unaff_A2 + 1) = *(char *)(unaff_A2 + 1) + '\x02';
  return;
}

