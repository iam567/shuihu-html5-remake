/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001581c */

void FUN_0001581c(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  char in_D1b;
  short unaff_D3w;
  int *piVar5;
  int *piVar6;
  
  piVar5 = (int *)&DAT_00015892;
  if (in_D1b != '\0') {
    piVar5 = (int *)&DAT_000158aa;
  }
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6));
  while (*piVar5 != 0x12345678) {
    sVar3 = *(short *)piVar5 + (uVar1 >> 5);
    piVar6 = piVar5 + 1;
    sVar4 = (short)*piVar5 + (uVar2 >> 5);
    piVar5 = piVar6;
    if ((((-1 < sVar3) && ((char)sVar3 < DAT_00ffe108)) && (-1 < sVar4)) &&
       ((char)sVar4 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)((int)&DAT_00ffb000 + (int)unaff_D3w) = 0;
    }
  }
  return;
}

