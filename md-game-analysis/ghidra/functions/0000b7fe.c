/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000b7fe */

undefined8 FUN_0000b7fe(void)

{
  byte bVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  byte *pbVar2;
  
  pbVar2 = &DAT_000ad17c + *(short *)(&DAT_000ad17c + (short)((short)in_D1 << 1));
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
  return CONCAT44(in_D0,in_D1);
}

