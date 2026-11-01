/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000092f8 */

void FUN_000092f8(void)

{
  ushort uVar1;
  byte bVar2;
  ushort uVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  DAT_00ff60bd = 0xff;
  uVar3 = 1000;
  pbVar4 = &DAT_00ff7180;
  while( true ) {
    pbVar5 = pbVar4 + 1;
    bVar2 = *pbVar4;
    if (bVar2 == 0xff) break;
    uVar1 = *(ushort *)((int)&DAT_00ffe792 + (int)(short)((ushort)bVar2 << 6));
    pbVar4 = pbVar5;
    if (uVar1 <= uVar3) {
      uVar3 = uVar1;
      DAT_00ff60bd = bVar2;
    }
  }
  return;
}

