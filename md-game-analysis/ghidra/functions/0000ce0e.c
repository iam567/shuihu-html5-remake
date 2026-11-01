/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000ce0e */

char FUN_0000ce0e(void)

{
  char cVar1;
  short unaff_D3w;
  int unaff_A4;
  
  cVar1 = ('\n' - (char)(((uint)*(ushort *)(unaff_A4 + 0x12 + (int)unaff_D3w) * 10) /
                        (uint)*(ushort *)(unaff_A4 + 0x1e + (int)unaff_D3w))) * '\b';
  if (*(char *)(unaff_A4 + 0xd + (int)unaff_D3w) == '\0') {
    cVar1 = '\0';
  }
  return *(char *)(unaff_A4 + 0xf + (int)unaff_D3w) +
         *(char *)(unaff_A4 + 0xe + (int)unaff_D3w) +
         *(char *)(unaff_A4 + 0xc + (int)unaff_D3w) * '\x10' + cVar1;
}

