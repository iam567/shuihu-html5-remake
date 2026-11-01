/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001b9a8 */

void FUN_0001b9a8(void)

{
  short in_D0w;
  ushort uVar1;
  uint in_D1;
  int iVar2;
  short sVar3;
  short unaff_D2w;
  short unaff_D3w;
  undefined2 unaff_D4w;
  
  iVar2 = (in_D1 & 0xffff) * 0x80;
  uVar1 = (ushort)((uint)iVar2 >> 0x10);
  iVar2 = (CONCAT22(uVar1,in_D0w * 2 + (short)iVar2) << 0x10 | (uint)uVar1) + 0x40000003;
  do {
    Ram00c00004 = iVar2;
    sVar3 = unaff_D2w;
    do {
      Ram00c00000 = unaff_D4w;
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
    iVar2 = iVar2 + 0x800000;
    unaff_D3w = unaff_D3w + -1;
  } while (unaff_D3w != -1);
  return;
}

