/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000012ee */

undefined8 FUN_000012ee(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short unaff_D2w;
  uint unaff_A2;
  
  FUN_00001352();
  Ram00c00004 = 0x9300;
  Ram00c00004 = 0x9401;
  Ram00c00004 = (short)CONCAT31(0x95,(char)(unaff_A2 >> 1));
  Ram00c00004 = (short)CONCAT31(0x96,(char)((unaff_A2 >> 1) >> 8));
  Ram00c00004 = (short)CONCAT31(0x97,(char)((unaff_A2 >> 9) >> 8));
  Ram00c00004 = (uint)(ushort)(unaff_D2w << 9) * 0x10000 + 0x44000080;
  return CONCAT44(in_D0,in_D1);
}

