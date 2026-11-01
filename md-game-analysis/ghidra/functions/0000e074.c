/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000e074 */

void FUN_0000e074(void)

{
  short in_D1w;
  int unaff_A2;
  int iVar1;
  
  iVar1 = (short)(in_D1w << 6) + unaff_A2;
  DAT_00ff6052 = *(ushort *)(iVar1 + 2) >> 5;
  DAT_00ff6054 = *(ushort *)(iVar1 + 4) >> 5;
  DAT_00ff605a = 1;
  DAT_00ff6085 = 4;
  return;
}

