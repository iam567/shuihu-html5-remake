/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00015172 */

void FUN_00015172(void)

{
  ushort uVar1;
  short sVar2;
  uint uVar3;
  ushort uVar4;
  short unaff_D3w;
  short sVar5;
  int extraout_A1;
  int extraout_A1_00;
  char *pcVar6;
  int *unaff_A4;
  int *piVar7;
  char *pcVar8;
  char *pcVar9;
  
  uVar4 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2);
  uVar1 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6));
  FUN_0001509e();
  FUN_00009898();
  while (*unaff_A4 != 0x12345678) {
    sVar5 = *(short *)unaff_A4 + (uVar4 >> 5);
    piVar7 = unaff_A4 + 1;
    sVar2 = (short)*unaff_A4 + (uVar1 >> 5);
    unaff_A4 = piVar7;
    if ((((-1 < sVar5) && ((char)sVar5 < DAT_00ffe108)) && (-1 < sVar2)) &&
       ((char)sVar2 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)(extraout_A1 + unaff_D3w) = 0xff;
    }
  }
  uVar3 = 0;
  sVar5 = 0xb;
  do {
    uVar4 = (ushort)uVar3;
    if ((DAT_00ffe1e4 & 1 << (uVar3 & 0x1f)) == 0) break;
    uVar4 = uVar4 + 1;
    uVar3 = (uint)uVar4;
    sVar5 = sVar5 + -1;
  } while (sVar5 != -1);
  sVar5 = uVar4 - 1;
  pcVar6 = (char *)&DAT_00ffe780;
  uVar3 = 0;
  pcVar8 = &DAT_00ff7180;
  do {
    pcVar9 = pcVar8;
    if (((*pcVar6 != '\0') && ((DAT_00ffe1e0 & 1 << (uVar3 & 0x1f)) == 0)) &&
       (sVar5 = FUN_00006902(), *(char *)(extraout_A1_00 + unaff_D3w) == -1)) {
      pcVar9 = pcVar8 + 1;
      *pcVar8 = (char)uVar3;
    }
    uVar3 = (uint)(byte)((char)uVar3 + 1);
    pcVar6 = pcVar6 + 0x40;
    sVar5 = sVar5 + -1;
    pcVar8 = pcVar9;
  } while (sVar5 != -1);
  *pcVar9 = -1;
  return;
}

