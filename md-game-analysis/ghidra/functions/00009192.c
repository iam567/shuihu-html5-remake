/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009192 */

void FUN_00009192(void)

{
  ushort uVar1;
  short sVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  short sVar6;
  byte bVar7;
  char cVar8;
  byte *pbVar9;
  byte *pbVar10;
  
  bVar7 = 0;
  cVar8 = -1;
  pbVar9 = &DAT_00ff7180;
  while (*pbVar9 != 0xff) {
    sVar6 = (ushort)*pbVar9 << 6;
    uVar1 = *(ushort *)((int)&DAT_00ffe79e + (int)sVar6);
    sVar2 = *(short *)((int)&DAT_00ffe792 + (int)sVar6);
    cVar4 = *(char *)((int)&PTR_DAT_000091fe + (int)(short)(ushort)(byte)(&DAT_00ffe7a1)[sVar6]);
    cVar5 = FUN_0000920e();
    cVar5 = cVar5 + cVar4 + (char)(((uint)(ushort)(uVar1 - sVar2) * 10) / (uint)uVar1);
    pbVar10 = pbVar9 + 1;
    bVar3 = *pbVar9;
    if (bVar3 == 0) {
      cVar5 = cVar5 + '\x05';
    }
    pbVar9 = pbVar10;
    if (cVar8 < cVar5) {
      bVar7 = bVar3;
      cVar8 = cVar5;
    }
  }
  DAT_00ff609f = bVar7;
  return;
}

