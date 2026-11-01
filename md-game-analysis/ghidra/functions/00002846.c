/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00002846 */

undefined8 FUN_00002846(void)

{
  undefined4 in_D0;
  ushort uVar1;
  undefined4 in_D1;
  short sVar2;
  uint unaff_A2;
  
  if ((char)in_D1 != '\0') {
    sVar2 = (short)in_D1 << 4;
    Ram00c00004 = (short)CONCAT31(0x93,(char)sVar2);
    Ram00c00004 = (short)CONCAT31(0x94,(char)((ushort)sVar2 >> 8));
    Ram00c00004 = (short)CONCAT31(0x95,(char)(unaff_A2 >> 1));
    Ram00c00004 = (short)CONCAT31(0x96,(char)((unaff_A2 >> 1) >> 8));
    Ram00c00004 = (short)CONCAT31(0x97,(char)((unaff_A2 >> 9) >> 8));
    uVar1 = (short)in_D0 << 5;
    Ram00c00004 = (uint)(uVar1 & 0x3fff) * 0x10000 + CONCAT31(0x400000,(byte)(uVar1 >> 0xe) + 0x80);
  }
  return CONCAT44(in_D0,in_D1);
}

