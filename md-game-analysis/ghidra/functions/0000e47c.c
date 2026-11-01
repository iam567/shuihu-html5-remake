/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000e47c */

void FUN_0000e47c(void)

{
  int iVar1;
  
  FUN_00006f0e();
  FUN_00006986();
  iVar1 = (int)(short)((ushort)DAT_00ff606b << 6);
  DAT_00ff6064 = (*(ushort *)((int)&DAT_00ffe784 + iVar1) >> 5) +
                 (*(ushort *)((int)&DAT_00ffe780 + iVar1 + 2) >> 5) * 0x100;
  DAT_00ff60a8 = (&DAT_00ffe7a0)[iVar1];
  FUN_0000e4e0();
  FUN_00009334();
  FUN_00006c86();
  DAT_00ff6085 = 0xe;
  DAT_00ff6107 = 0;
  return;
}

