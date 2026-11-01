/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d148 */

void FUN_0000d148(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  short sVar5;
  short unaff_D3w;
  char cVar6;
  int extraout_A1;
  int extraout_A1_00;
  char *pcVar7;
  int *piVar8;
  int *piVar9;
  char *pcVar10;
  char *pcVar11;
  
  iVar4 = (int)(short)((ushort)DAT_00ff606b << 6);
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + iVar4 + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + iVar4);
  piVar8 = (int *)&DAT_0000d21e;
  if (((&DAT_00ffe7a4)[iVar4] != '\x1a') &&
     (piVar8 = (int *)&DAT_0000d252, (&DAT_00ffe7a4)[iVar4] != '\x1b')) {
    piVar8 = (int *)&DAT_0000d2b6;
  }
  FUN_00009898();
  while (*piVar8 != 0x12345678) {
    sVar5 = *(short *)piVar8 + (uVar1 >> 5);
    piVar9 = piVar8 + 1;
    sVar3 = (short)*piVar8 + (uVar2 >> 5);
    piVar8 = piVar9;
    if ((((-1 < sVar5) && ((char)sVar5 < DAT_00ffe108)) && (-1 < sVar3)) &&
       ((char)sVar3 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)(extraout_A1 + unaff_D3w) = 0xff;
    }
  }
  pcVar7 = &DAT_00ffea80;
  cVar6 = '\f';
  sVar5 = 0x11;
  pcVar10 = &DAT_00ff7180;
  do {
    pcVar11 = pcVar10;
    if ((*pcVar7 != '\0') && (sVar5 = FUN_00006902(), *(char *)(extraout_A1_00 + unaff_D3w) == -1))
    {
      pcVar11 = pcVar10 + 1;
      *pcVar10 = cVar6;
    }
    cVar6 = cVar6 + '\x01';
    pcVar7 = pcVar7 + 0x40;
    sVar5 = sVar5 + -1;
    pcVar10 = pcVar11;
  } while (sVar5 != -1);
  *pcVar11 = -1;
  return;
}

