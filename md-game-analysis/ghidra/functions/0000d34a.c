/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d34a */

void FUN_0000d34a(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  short unaff_D3w;
  int *piVar6;
  int *piVar7;
  
  iVar5 = (int)(short)((ushort)DAT_00ff606b << 6);
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + iVar5 + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + iVar5);
  piVar6 = (int *)&DAT_0000d21e;
  if (((&DAT_00ffe7a4)[iVar5] != '\x1a') &&
     (piVar6 = (int *)&DAT_0000d252, (&DAT_00ffe7a4)[iVar5] != '\x1b')) {
    piVar6 = (int *)&DAT_0000d2b6;
  }
  while (*piVar6 != 0x12345678) {
    sVar3 = *(short *)piVar6 + (uVar1 >> 5);
    piVar7 = piVar6 + 1;
    sVar4 = (short)*piVar6 + (uVar2 >> 5);
    piVar6 = piVar7;
    if ((((-1 < sVar3) && ((char)sVar3 < DAT_00ffe108)) && (-1 < sVar4)) &&
       ((char)sVar4 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)((int)&DAT_00ffb000 + (int)unaff_D3w) = 0;
    }
  }
  return;
}

