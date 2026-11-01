/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000152ce */

void FUN_000152ce(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  uint uVar5;
  short unaff_D3w;
  char cVar6;
  int extraout_A1;
  int extraout_A1_00;
  char *pcVar7;
  int *unaff_A4;
  int *piVar8;
  char *pcVar9;
  char *pcVar10;
  
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6));
  FUN_0001509e();
  FUN_00009898();
  while (*unaff_A4 != 0x12345678) {
    sVar4 = *(short *)unaff_A4 + (uVar1 >> 5);
    piVar8 = unaff_A4 + 1;
    sVar3 = (short)*unaff_A4 + (uVar2 >> 5);
    unaff_A4 = piVar8;
    if ((((-1 < sVar4) && ((char)sVar4 < DAT_00ffe108)) && (-1 < sVar3)) &&
       ((char)sVar3 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)(extraout_A1 + unaff_D3w) = 0xff;
    }
  }
  pcVar7 = (char *)&DAT_00ffe780;
  cVar6 = '\0';
  sVar4 = 0xb;
  pcVar9 = &DAT_00ff7180;
  do {
    pcVar10 = pcVar9;
    if (*pcVar7 != '\0') {
      uVar5 = (uint)(byte)pcVar7[0xc];
      if (((DAT_00ff60bb != '\a') && (uVar5 = (uint)(byte)pcVar7[0xd], DAT_00ff60bb != '\b')) &&
         ((uVar5 = (uint)(byte)pcVar7[0xe], DAT_00ff60bb != '\t' &&
          (uVar5 = (uint)(byte)pcVar7[0xf], DAT_00ff60bb != '\n')))) {
        uVar5 = *(uint *)(pcVar7 + 0xc);
      }
      if ((uVar5 != 0) && (sVar4 = FUN_00006902(), *(char *)(extraout_A1_00 + unaff_D3w) == -1)) {
        pcVar10 = pcVar9 + 1;
        *pcVar9 = cVar6;
      }
    }
    cVar6 = cVar6 + '\x01';
    pcVar7 = pcVar7 + 0x40;
    sVar4 = sVar4 + -1;
    pcVar9 = pcVar10;
  } while (sVar4 != -1);
  *pcVar10 = -1;
  return;
}

