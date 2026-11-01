/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009ad6 */

void FUN_00009ad6(void)

{
  short sVar1;
  short sVar2;
  short unaff_D3w;
  undefined2 unaff_D4w;
  short sVar3;
  undefined2 unaff_D5w;
  short sVar4;
  int *unaff_A4;
  int *piVar5;
  
  FUN_00009898();
  FUN_0000ae84();
  sVar3 = CONCAT11((char)((ushort)unaff_D4w >> 8),DAT_00ff6088);
  sVar4 = CONCAT11((char)((ushort)unaff_D5w >> 8),DAT_00ff6089);
  while (*unaff_A4 != 0x12345678) {
    sVar1 = *(short *)unaff_A4 + sVar3;
    piVar5 = unaff_A4 + 1;
    sVar2 = (short)*unaff_A4 + sVar4;
    unaff_A4 = piVar5;
    if ((((-1 < sVar1) && ((char)sVar1 < DAT_00ffe108)) && (-1 < sVar2)) &&
       ((char)sVar2 < DAT_00ffe109)) {
      FUN_00006902();
      (&DAT_00ff5000)[unaff_D3w] = 0xff;
    }
  }
  return;
}

