/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000097dc */

void FUN_000097dc(void)

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
  char *pcVar9;
  char *pcVar10;
  
  FUN_00009898();
  FUN_000098ae();
  pcVar7 = (char *)&DAT_00ffe780;
  cVar6 = '\0';
  sVar5 = 0xb;
  pcVar9 = &DAT_00ff7180;
  if (DAT_00ffe1f7 != '\x02') {
    pcVar7 = &DAT_00ffea80;
    cVar6 = '\f';
    sVar5 = 0x11;
  }
  do {
    pcVar10 = pcVar9;
    if (*pcVar7 != '\0') {
      uVar1 = *(ushort *)(pcVar7 + 2);
      uVar2 = *(ushort *)(pcVar7 + 4);
      sVar5 = FUN_0000ae84();
      piVar8 = unaff_A4;
      do {
        unaff_A4 = piVar8;
        if (*piVar8 == 0x12345678) goto LAB_00009884;
        sVar3 = *(short *)piVar8 + (uVar1 >> 5);
        unaff_A4 = piVar8 + 1;
        sVar4 = (short)*piVar8 + (uVar2 >> 5);
        piVar8 = unaff_A4;
      } while ((((sVar3 < 0) || (DAT_00ffe108 <= (char)sVar3)) || (sVar4 < 0)) ||
              (((DAT_00ffe109 <= (char)sVar4 ||
                (sVar5 = FUN_00006902(), 0x7e < *(byte *)((int)&DAT_00ffb000 + (int)unaff_D3w))) ||
               (*(char *)(extraout_A1 + unaff_D3w) == -1))));
      pcVar10 = pcVar9 + 1;
      *pcVar9 = cVar6;
    }
LAB_00009884:
    cVar6 = cVar6 + '\x01';
    pcVar7 = pcVar7 + 0x40;
    sVar5 = sVar5 + -1;
    pcVar9 = pcVar10;
    if (sVar5 == -1) {
      *pcVar10 = -1;
      return;
    }
  } while( true );
}

