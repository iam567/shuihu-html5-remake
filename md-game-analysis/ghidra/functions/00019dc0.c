/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00019dc0 */

undefined8 FUN_00019dc0(void)

{
  byte bVar1;
  undefined4 in_D0;
  short sVar2;
  undefined4 in_D1;
  byte *pbVar3;
  
  sVar2 = 0x4c0;
  pbVar3 = &DAT_000ad830 + *(short *)(&DAT_000ad830 + (short)((short)in_D1 << 1));
  while( true ) {
    bVar1 = *pbVar3;
    if (bVar1 == 0xff) break;
    if (bVar1 < 0xf0) {
      FUN_0000b970();
      FUN_0000b98c();
      sVar2 = FUN_0000ba5c();
      sVar2 = sVar2 + 4;
      pbVar3 = pbVar3 + 1;
    }
    else {
      DAT_00ff60b3 = bVar1 + 0x10;
      pbVar3 = pbVar3 + 1;
    }
  }
  if (sVar2 != 0x500) {
    FUN_0001977c();
  }
  return CONCAT44(in_D0,in_D1);
}

