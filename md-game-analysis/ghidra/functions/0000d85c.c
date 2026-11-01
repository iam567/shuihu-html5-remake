/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d85c */

void FUN_0000d85c(void)

{
  ushort uVar1;
  ushort uVar2;
  byte bVar3;
  short sVar4;
  int iVar5;
  short sVar6;
  short unaff_D3w;
  char cVar7;
  int extraout_A1;
  int extraout_A1_00;
  char *pcVar8;
  int *piVar9;
  int *piVar10;
  char *pcVar11;
  char *pcVar12;
  
  iVar5 = (int)(short)((ushort)DAT_00ff606b << 6);
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + iVar5 + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + iVar5);
  piVar9 = (int *)&DAT_0000d21e;
  if (((&DAT_00ffe7a4)[iVar5] != '\x1a') &&
     (piVar9 = (int *)&DAT_0000d252, (&DAT_00ffe7a4)[iVar5] != '\x1b')) {
    piVar9 = (int *)&DAT_0000d2b6;
  }
  FUN_00009898();
  while (*piVar9 != 0x12345678) {
    sVar6 = *(short *)piVar9 + (uVar1 >> 5);
    piVar10 = piVar9 + 1;
    sVar4 = (short)*piVar9 + (uVar2 >> 5);
    piVar9 = piVar10;
    if ((((-1 < sVar6) && ((char)sVar6 < DAT_00ffe108)) && (-1 < sVar4)) &&
       ((char)sVar4 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)(extraout_A1 + unaff_D3w) = 0xff;
    }
  }
  bVar3 = DAT_00ff610c + 9;
  pcVar8 = (char *)&DAT_00ffe780;
  cVar7 = '\0';
  sVar6 = 0xb;
  pcVar11 = &DAT_00ff7180;
  if (DAT_00ffe1f7 != '\x02') {
    pcVar8 = &DAT_00ffea80;
    cVar7 = '\f';
    sVar6 = 0x11;
  }
  do {
    pcVar12 = pcVar11;
    if (((*pcVar8 != '\0') && (pcVar8[(short)(ushort)bVar3] == '\0')) &&
       (sVar6 = FUN_00006902(), *(char *)(extraout_A1_00 + unaff_D3w) == -1)) {
      pcVar12 = pcVar11 + 1;
      *pcVar11 = cVar7;
    }
    cVar7 = cVar7 + '\x01';
    pcVar8 = pcVar8 + 0x40;
    sVar6 = sVar6 + -1;
    pcVar11 = pcVar12;
  } while (sVar6 != -1);
  *pcVar12 = -1;
  return;
}

