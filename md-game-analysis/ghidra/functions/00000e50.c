/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00000e50 */

uint Seed_e50(void)

{
  uint uVar1;
  int iVar2;
  ushort uVar3;
  undefined4 in_D0;
  short *unaff_A2;
  
  uVar3 = (ushort)((uint)in_D0 >> 0x10);
  iVar2 = (CONCAT22(uVar3,(short)in_D0 << 5) << 0x10 | (uint)uVar3) << 2;
  uVar1 = CONCAT31((uint3)((uint)iVar2 >> 10),(byte)iVar2 | ((byte)((uint)in_D0 >> 8) & 7) >> 1) |
          0x40000000;
  Ram00c00004 = uVar1;
  while (*unaff_A2 != 0x3402) {
    Ram00c00000 = *unaff_A2;
    unaff_A2 = unaff_A2 + 1;
  }
  return uVar1;
}

