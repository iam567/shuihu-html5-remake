/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006c86 */

void FUN_00006c86(void)

{
  byte bVar1;
  ushort uVar2;
  ushort extraout_D1w;
  ushort uVar3;
  short unaff_D3w;
  short sVar4;
  short sVar5;
  byte *pbVar6;
  byte *pbVar7;
  
  FUN_00009c4a();
  bVar1 = DAT_00ffe106 - 10;
  FUN_00006902();
  pbVar6 = (byte *)((int)&DAT_00ffb000 + (int)unaff_D3w);
  uVar3 = (ushort)DAT_00ff6035;
  sVar4 = 6;
  do {
    uVar2 = (ushort)DAT_00ff6034;
    sVar5 = 9;
    do {
      pbVar7 = pbVar6 + 1;
      if (*pbVar6 < 0x7f) {
        uVar2 = FUN_0000309a();
        uVar3 = extraout_D1w;
      }
      uVar2 = uVar2 + 4;
      if (uVar2 == 0x40) {
        uVar2 = 0;
      }
      sVar5 = sVar5 + -1;
      pbVar6 = pbVar7;
    } while (sVar5 != -1);
    pbVar6 = pbVar7 + (short)(ushort)bVar1;
    uVar3 = uVar3 + 4;
    if (uVar3 == 0x20) {
      uVar3 = 0;
    }
    sVar4 = sVar4 + -1;
  } while (sVar4 != -1);
  return;
}

