/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000159fc */

void FUN_000159fc(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  short unaff_D3w;
  char cVar5;
  int extraout_A1;
  int extraout_A1_00;
  char *pcVar6;
  int *piVar7;
  int *piVar8;
  char *pcVar9;
  char *pcVar10;
  
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6));
  FUN_00009898();
  piVar7 = (int *)&DAT_000158aa;
  while (*piVar7 != 0x12345678) {
    sVar4 = *(short *)piVar7 + (uVar1 >> 5);
    piVar8 = piVar7 + 1;
    sVar3 = (short)*piVar7 + (uVar2 >> 5);
    piVar7 = piVar8;
    if ((((-1 < sVar4) && ((char)sVar4 < DAT_00ffe108)) && (-1 < sVar3)) &&
       ((char)sVar3 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)(extraout_A1 + unaff_D3w) = 0xff;
    }
  }
  pcVar6 = &DAT_00ffea80;
  cVar5 = '\f';
  sVar4 = 0x11;
  pcVar9 = &DAT_00ff7180;
  do {
    pcVar10 = pcVar9;
    if ((*pcVar6 != '\0') && (sVar4 = FUN_00006902(), *(char *)(extraout_A1_00 + unaff_D3w) == -1))
    {
      pcVar10 = pcVar9 + 1;
      *pcVar9 = cVar5;
    }
    cVar5 = cVar5 + '\x01';
    pcVar6 = pcVar6 + 0x40;
    sVar4 = sVar4 + -1;
    pcVar9 = pcVar10;
  } while (sVar4 != -1);
  *pcVar10 = -1;
  return;
}

