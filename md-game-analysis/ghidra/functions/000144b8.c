/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000144b8 */

void FUN_000144b8(void)

{
  byte bVar1;
  byte *unaff_A3;
  
  while( true ) {
    bVar1 = *unaff_A3;
    if (bVar1 == 0xff) break;
    if (bVar1 < 0xf0) {
      FUN_0000b970();
      FUN_0000b98c();
      FUN_0000ba5c();
      unaff_A3 = unaff_A3 + 1;
    }
    else {
      DAT_00ff60b3 = bVar1 + 0x10;
      unaff_A3 = unaff_A3 + 1;
    }
  }
  return;
}

