/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000163ee */

void FUN_000163ee(void)

{
  int iVar1;
  short sVar2;
  byte bVar3;
  byte *pbVar4;
  
  pbVar4 = &DAT_00ff7180;
  while( true ) {
    if (*pbVar4 == 0xff) break;
    iVar1 = (int)(short)((ushort)*pbVar4 << 6);
    bVar3 = DAT_00ff6156 - (&DAT_00ffe796)[iVar1];
    if ((char)bVar3 < '\x01') {
      bVar3 = 1;
    }
    sVar2 = *(short *)((int)&DAT_00ffe792 + iVar1) - (ushort)bVar3;
    if (sVar2 < 1) {
      sVar2 = 0;
      (&DAT_00ffe7af)[iVar1] = 1;
    }
    *(short *)((int)&DAT_00ffe792 + iVar1) = sVar2;
    DAT_00ff60ac = 2;
    FUN_0000b3ec();
    pbVar4 = pbVar4 + 1;
  }
  return;
}

