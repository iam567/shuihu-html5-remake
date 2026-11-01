/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000039ce */

void FUN_000039ce(void)

{
  ushort in_D1w;
  
  if (DAT_00ffe10a != '\0') {
    if ((DAT_00ffe10a != '\x01') && (in_D1w = in_D1w >> 1, in_D1w == 0)) {
      if ((DAT_00ff6039 & 1) != 0) {
        return;
      }
      in_D1w = 1;
    }
    DAT_00ff600c = DAT_00ff600c - in_D1w;
  }
  return;
}

