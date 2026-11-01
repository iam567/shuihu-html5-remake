/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000158be */

void FUN_000158be(void)

{
  ushort uVar1;
  ushort uVar2;
  char cVar3;
  short sVar4;
  short sVar5;
  short unaff_D3w;
  char cVar6;
  int extraout_A1;
  int extraout_A1_00;
  char *pcVar7;
  int *piVar8;
  int *piVar9;
  char *pcVar10;
  
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6));
  FUN_00009898();
  piVar8 = (int *)&DAT_00015892;
  while (*piVar8 != 0x12345678) {
    sVar5 = *(short *)piVar8 + (uVar1 >> 5);
    piVar9 = piVar8 + 1;
    sVar4 = (short)*piVar8 + (uVar2 >> 5);
    piVar8 = piVar9;
    if ((((-1 < sVar5) && ((char)sVar5 < DAT_00ffe108)) && (-1 < sVar4)) &&
       ((char)sVar4 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)(extraout_A1 + unaff_D3w) = 0xff;
    }
  }
  pcVar10 = &DAT_00ff7180;
  pcVar7 = (char *)&DAT_00ffe780;
  cVar6 = '\0';
  sVar5 = 0xb;
  do {
    if ((*pcVar7 != '\0') && (sVar5 = FUN_00006902(), *(char *)(extraout_A1_00 + unaff_D3w) == -1))
    {
      if (DAT_00ff60bb == '\0') {
        if (*(short *)(pcVar7 + 0x12) != *(short *)(pcVar7 + 0x1e)) {
LAB_000159e6:
          *pcVar10 = cVar6;
          pcVar10 = pcVar10 + 1;
        }
      }
      else {
        if (DAT_00ff60bb == '\x01') {
          cVar3 = pcVar7[0xc];
        }
        else if (DAT_00ff60bb == '\x02') {
          cVar3 = pcVar7[0xd];
        }
        else if (DAT_00ff60bb == '\x03') {
          cVar3 = pcVar7[0xe];
        }
        else {
          if (DAT_00ff60bb != '\x04') goto LAB_000159e6;
          cVar3 = pcVar7[0xf];
        }
        if (cVar3 != '\0') goto LAB_000159e6;
      }
    }
    cVar6 = cVar6 + '\x01';
    pcVar7 = pcVar7 + 0x40;
    sVar5 = sVar5 + -1;
    if (sVar5 == -1) {
      *pcVar10 = -1;
      return;
    }
  } while( true );
}

