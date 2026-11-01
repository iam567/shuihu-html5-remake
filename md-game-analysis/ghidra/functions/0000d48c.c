/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d48c */

void FUN_0000d48c(void)

{
  ushort uVar1;
  ushort uVar2;
  byte bVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short unaff_D3w;
  char cVar7;
  int extraout_A1;
  char *pcVar8;
  int *piVar9;
  int *piVar10;
  char *pcVar11;
  char *pcVar12;
  
  FUN_00009898();
  FUN_000098ae();
  bVar3 = DAT_00ff610c + 9;
  DAT_00ff60f0 = (int *)&DAT_0000d21e;
  if (((&DAT_00ffe7a4)[(short)((ushort)DAT_00ff606b << 6)] != '\x1a') &&
     (DAT_00ff60f0 = (int *)&DAT_0000d252,
     (&DAT_00ffe7a4)[(short)((ushort)DAT_00ff606b << 6)] != '\x1b')) {
    DAT_00ff60f0 = (int *)&DAT_0000d2b6;
  }
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
    if ((*pcVar8 != '\0') && (pcVar8[(short)(ushort)bVar3] == '\0')) {
      uVar1 = *(ushort *)(pcVar8 + 2);
      uVar2 = *(ushort *)(pcVar8 + 4);
      piVar9 = DAT_00ff60f0;
      do {
        if (*piVar9 == 0x12345678) goto LAB_0000d588;
        sVar4 = *(short *)piVar9 + (uVar1 >> 5);
        piVar10 = piVar9 + 1;
        sVar5 = (short)*piVar9 + (uVar2 >> 5);
        piVar9 = piVar10;
      } while ((((sVar4 < 0) || (DAT_00ffe108 <= (char)sVar4)) || (sVar5 < 0)) ||
              (((DAT_00ffe109 <= (char)sVar5 ||
                (sVar6 = FUN_00006902(), 0x7e < *(byte *)((int)&DAT_00ffb000 + (int)unaff_D3w))) ||
               (*(char *)(extraout_A1 + unaff_D3w) == -1))));
      pcVar12 = pcVar11 + 1;
      *pcVar11 = cVar7;
    }
LAB_0000d588:
    cVar7 = cVar7 + '\x01';
    pcVar8 = pcVar8 + 0x40;
    sVar6 = sVar6 + -1;
    pcVar11 = pcVar12;
    if (sVar6 == -1) {
      *pcVar12 = -1;
      return;
    }
  } while( true );
}

