/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001a6b0 */

void FUN_0001a6b0(void)

{
  byte bVar1;
  short in_D1w;
  byte *pbVar2;
  
  pbVar2 = *(byte **)((int)&PTR_DAT_0001a6fc + (int)(short)(in_D1w << 2));
  while( true ) {
    bVar1 = *pbVar2;
    if (bVar1 == 0xff) break;
    if (bVar1 < 0xf0) {
      FUN_0000b970();
      FUN_0000b98c();
      FUN_0000ba5c();
      pbVar2 = pbVar2 + 1;
    }
    else {
      DAT_00ff60b3 = bVar1 + 0x10;
      pbVar2 = pbVar2 + 1;
    }
  }
  return;
}

