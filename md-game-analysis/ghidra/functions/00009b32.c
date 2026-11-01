/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009b32 */

void FUN_00009b32(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  short unaff_D3w;
  int *unaff_A4;
  int *piVar5;
  
  FUN_0000ae84();
  uVar1 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2);
  uVar2 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6));
  while (*unaff_A4 != 0x12345678) {
    sVar3 = *(short *)unaff_A4 + (uVar1 >> 5);
    piVar5 = unaff_A4 + 1;
    sVar4 = (short)*unaff_A4 + (uVar2 >> 5);
    unaff_A4 = piVar5;
    if ((((-1 < sVar3) && ((char)sVar3 < DAT_00ffe108)) && (-1 < sVar4)) &&
       ((char)sVar4 < DAT_00ffe109)) {
      FUN_00006902();
      *(undefined1 *)((int)&DAT_00ffb000 + (int)unaff_D3w) = 0;
    }
  }
  return;
}

