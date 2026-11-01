/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003a0a */

void FUN_00003a0a(void)

{
  ushort in_D1w;
  
  if (DAT_00ffe10a != '\0') {
    if ((DAT_00ffe10a != '\x01') && (in_D1w = in_D1w >> 1, in_D1w == 0)) {
      if ((DAT_00ff6039 & 1) != 0) {
        return;
      }
      in_D1w = 1;
    }
    DAT_00ff600e = in_D1w + DAT_00ff600e;
  }
  return;
}

