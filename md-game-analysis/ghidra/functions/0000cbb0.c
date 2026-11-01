/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000cbb0 */

void FUN_0000cbb0(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short unaff_D3w;
  char cVar6;
  int extraout_A1;
  char *pcVar7;
  int *unaff_A4;
  int *piVar8;
  int *piVar9;
  char *pcVar10;
  char *pcVar11;
  
  FUN_00009898();
  FUN_000098ae();
  FUN_0001509e();
  pcVar7 = &DAT_00ffea80;
  cVar6 = '\f';
  sVar5 = 0x11;
  pcVar10 = &DAT_00ff7180;
  DAT_00ff60f0 = unaff_A4;
  if (DAT_00ffe1f7 != '\x02') {
    pcVar7 = (char *)&DAT_00ffe780;
    cVar6 = '\0';
    sVar5 = 0xb;
  }
  do {
    pcVar11 = pcVar10;
    if ((*pcVar7 != '\0') && (*(int *)(pcVar7 + 0xc) != 0)) {
      uVar1 = *(ushort *)(pcVar7 + 2);
      uVar2 = *(ushort *)(pcVar7 + 4);
      piVar8 = DAT_00ff60f0;
      do {
        if (*piVar8 == 0x12345678) goto LAB_0000cc84;
        sVar3 = *(short *)piVar8 + (uVar1 >> 5);
        piVar9 = piVar8 + 1;
        sVar4 = (short)*piVar8 + (uVar2 >> 5);
        piVar8 = piVar9;
      } while ((((sVar3 < 0) || (DAT_00ffe108 <= (char)sVar3)) || (sVar4 < 0)) ||
              (((DAT_00ffe109 <= (char)sVar4 ||
                (sVar5 = FUN_00006902(), 0x7e < *(byte *)((int)&DAT_00ffb000 + (int)unaff_D3w))) ||
               (*(char *)(extraout_A1 + unaff_D3w) == -1))));
      pcVar11 = pcVar10 + 1;
      *pcVar10 = cVar6;
    }
LAB_0000cc84:
    cVar6 = cVar6 + '\x01';
    pcVar7 = pcVar7 + 0x40;
    sVar5 = sVar5 + -1;
    pcVar10 = pcVar11;
    if (sVar5 == -1) {
      *pcVar11 = -1;
      return;
    }
  } while( true );
}

