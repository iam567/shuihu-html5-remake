/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e77d8 */

void FUN_001e77d8(void)

{
  char unaff_D6b;
  
  if (unaff_D6b == -0x40) {
    DAT_00c00011 = 0xff;
  }
  else {
    DAT_00c00011 = unaff_D6b + 0x10U | 0xf;
  }
  return;
}

