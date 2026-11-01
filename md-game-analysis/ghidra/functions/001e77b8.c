/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e77b8 */

byte FUN_001e77b8(void)

{
  byte bVar1;
  char unaff_D6b;
  int unaff_A5;
  
  if (unaff_D6b == -0x40) {
    bVar1 = 0xf0;
  }
  else {
    bVar1 = unaff_D6b + 0x10;
  }
  bVar1 = *(byte *)(unaff_A5 + 6) | bVar1;
  DAT_00c00011 = bVar1;
  return bVar1;
}

