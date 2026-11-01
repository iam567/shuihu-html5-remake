/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000275e6 */

void FUN_000275e6(void)

{
  ushort uVar1;
  short sVar2;
  byte bVar4;
  short sVar3;
  short sVar5;
  undefined2 *unaff_A2;
  byte *pbVar6;
  short *psVar7;
  
  if ((DAT_00ff61bc != 0) && ((DAT_00ff6010 & 1) == 0)) {
    DAT_00ff61bc = DAT_00ff61bc + 1;
    if (DAT_00ff61bc == 0x140) {
      DAT_00ff61be = 1;
      DAT_00ff611a = 0;
    }
    uVar1 = 0x17;
    pbVar6 = &DAT_00ff61c0;
    psVar7 = &DAT_00ff61d8;
    do {
      bVar4 = *pbVar6 + 1;
      if (0x2f < bVar4) {
        bVar4 = 0;
      }
      *pbVar6 = bVar4;
      sVar3 = 4;
      if ((uVar1 < 0x10) && (sVar3 = 3, uVar1 < 8)) {
        sVar3 = 2;
      }
      *psVar7 = *psVar7 - sVar3;
      uVar1 = uVar1 - 1;
      pbVar6 = pbVar6 + 1;
      psVar7 = psVar7 + 1;
    } while (uVar1 != 0xffff);
    sVar3 = 0;
    sVar2 = 0x17;
    do {
      sVar5 = sVar3 << 1;
      if (*(short *)((int)&DAT_00ff61d8 + (int)sVar5) < 0x1c1) {
        unaff_A2[2] = *(byte *)((int)&PTR_DAT_000276c6 +
                               (int)(short)(ushort)((byte)(&DAT_00ff61c0)[sVar3] >> 3)) + 0x9d;
        *unaff_A2 = *(undefined2 *)((int)&DAT_00ff61d8 + (int)sVar5);
        unaff_A2[1] = *(undefined2 *)((int)&DAT_0002773a + (int)sVar5);
        DAT_00ff6012 = DAT_00ff6012 + 1;
        unaff_A2 = unaff_A2 + 3;
      }
      sVar3 = sVar3 + 1;
      sVar2 = sVar2 + -1;
    } while (sVar2 != -1);
  }
  return;
}

