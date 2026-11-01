/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000fac0 */

undefined8 FUN_0000fac0(void)

{
  int iVar1;
  ushort uVar2;
  undefined4 in_D0;
  short sVar3;
  undefined4 in_D1;
  char unaff_D2b;
  
  uVar2 = (ushort)((uint)in_D0 >> 0x10);
  sVar3 = 0x540;
  if ((unaff_D2b != '\0') && (sVar3 = 0x580, unaff_D2b != '\x10')) {
    sVar3 = 0x5c0;
  }
  iVar1 = (CONCAT22(uVar2,sVar3 << 5) << 0x10 | (uint)uVar2) << 2;
  Ram00c00004 = CONCAT31((uint3)((uint)iVar1 >> 10),(byte)iVar1 | (byte)((ushort)sVar3 >> 9)) |
                0x40000000;
  sVar3 = 0x3f;
  do {
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    Ram00c00000 = 0xdddd;
    sVar3 = sVar3 + -1;
  } while (sVar3 != -1);
  return CONCAT44(in_D0,in_D1);
}

