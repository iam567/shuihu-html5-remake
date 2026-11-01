/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009b9a */

void FUN_00009b9a(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  short sVar5;
  char cVar6;
  char *pcVar7;
  int *unaff_A4;
  int *piVar8;
  char *pcVar9;
  
  FUN_0000ae84();
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6));
  pcVar9 = &DAT_00ff7180;
  do {
    do {
      if (*unaff_A4 == 0x12345678) {
        *pcVar9 = -1;
        return;
      }
      uVar3 = *(short *)unaff_A4 + (uVar1 >> 5);
      piVar8 = unaff_A4 + 1;
      uVar4 = (short)*unaff_A4 + (uVar2 >> 5);
      unaff_A4 = piVar8;
    } while (((((short)uVar3 < 0) || (DAT_00ffe108 <= (char)uVar3)) || ((short)uVar4 < 0)) ||
            (DAT_00ffe109 <= (char)uVar4));
    pcVar7 = &DAT_00ffea80;
    cVar6 = '\f';
    sVar5 = 0x11;
    do {
      if ((*pcVar7 != '\0') &&
         ((uint)uVar4 + (uint)uVar3 * 0x10000 ==
          (uint)(*(ushort *)(pcVar7 + 2) >> 5) * 0x10000 + (uint)(*(ushort *)(pcVar7 + 4) >> 5))) {
        *pcVar9 = cVar6;
        pcVar9 = pcVar9 + 1;
        break;
      }
      cVar6 = cVar6 + '\x01';
      pcVar7 = pcVar7 + 0x40;
      sVar5 = sVar5 + -1;
    } while (sVar5 != -1);
  } while( true );
}

