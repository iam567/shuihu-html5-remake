/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009a6c */

void FUN_00009a6c(void)

{
  short sVar1;
  short sVar2;
  short unaff_D3w;
  ushort uVar3;
  ushort uVar4;
  int extraout_A0;
  int *piVar5;
  int *piVar6;
  int *extraout_A1;
  
  uVar3 = (ushort)DAT_00ff6088;
  uVar4 = (ushort)DAT_00ff6089;
  piVar5 = *(int **)(&DAT_0000aeb2 + (short)((ushort)(byte)(DAT_00ff60be - 1) << 2));
  while (*piVar5 != 0x12345678) {
    sVar1 = *(short *)piVar5;
    piVar6 = piVar5 + 1;
    sVar2 = (short)*piVar5 + uVar4;
    piVar5 = piVar6;
    if ((((-1 < (short)(sVar1 + uVar3)) && ((char)(sVar1 + uVar3) < DAT_00ffe108)) && (-1 < sVar2))
       && ((char)sVar2 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)(extraout_A0 + unaff_D3w) = 0xec;
      piVar5 = extraout_A1;
    }
  }
  return;
}

