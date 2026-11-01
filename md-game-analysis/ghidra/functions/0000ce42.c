/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000ce42 */

void FUN_0000ce42(void)

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
  int *unaff_A4;
  int *piVar7;
  char *pcVar8;
  char *pcVar9;
  
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6));
  FUN_0001509e();
  FUN_00009898();
  while (*unaff_A4 != 0x12345678) {
    sVar4 = *(short *)unaff_A4 + (uVar1 >> 5);
    piVar7 = unaff_A4 + 1;
    sVar3 = (short)*unaff_A4 + (uVar2 >> 5);
    unaff_A4 = piVar7;
    if ((((-1 < sVar4) && ((char)sVar4 < DAT_00ffe108)) && (-1 < sVar3)) &&
       ((char)sVar3 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)(extraout_A1 + unaff_D3w) = 0xff;
    }
  }
  pcVar6 = &DAT_00ffea80;
  cVar5 = '\f';
  sVar4 = 0x11;
  pcVar8 = &DAT_00ff7180;
  do {
    pcVar9 = pcVar8;
    if (((*pcVar6 != '\0') && (*(int *)(pcVar6 + 0xc) != 0)) &&
       (sVar4 = FUN_00006902(), *(char *)(extraout_A1_00 + unaff_D3w) == -1)) {
      pcVar9 = pcVar8 + 1;
      *pcVar8 = cVar5;
    }
    cVar5 = cVar5 + '\x01';
    pcVar6 = pcVar6 + 0x40;
    sVar4 = sVar4 + -1;
    pcVar8 = pcVar9;
  } while (sVar4 != -1);
  *pcVar9 = -1;
  return;
}

