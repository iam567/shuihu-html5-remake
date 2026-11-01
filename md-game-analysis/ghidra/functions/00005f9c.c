/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00005f9c */

ushort FUN_00005f9c(void)

{
  byte bVar1;
  ushort uVar2;
  ushort unaff_D2w;
  
  bVar1 = (&DAT_00ffe798)[(short)((ushort)DAT_00ff606b << 6)];
  uVar2 = FUN_0000604e();
  if ((byte)((ushort)((DAT_00ff6100 & 0x3f) * 100) >> 6) <= bVar1) {
    uVar2 = unaff_D2w >> 1;
    DAT_00ff6103 = 2;
  }
  return uVar2;
}

