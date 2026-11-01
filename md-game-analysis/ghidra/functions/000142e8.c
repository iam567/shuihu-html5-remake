/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000142e8 */

void FUN_000142e8(void)

{
  byte bVar1;
  byte *pbVar2;
  
  FUN_00006f50();
  pbVar2 = &DAT_00014354;
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
  FUN_0001435e();
  return;
}

