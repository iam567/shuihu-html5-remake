/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000f9e6 */

void FUN_0000f9e6(void)

{
  int iVar1;
  ushort uVar2;
  undefined4 in_D0;
  short sVar3;
  byte bVar4;
  
  if (DAT_00ff6127 != 0) {
    uVar2 = (ushort)((uint)in_D0 >> 0x10);
    sVar3 = 0x540;
    bVar4 = DAT_00ff6127;
    while (bVar4 = bVar4 - 1, bVar4 != 0) {
      sVar3 = sVar3 + 0x20;
    }
    iVar1 = (CONCAT22(uVar2,sVar3 << 5) << 0x10 | (uint)uVar2) << 2;
    Ram00c00004 = CONCAT31((uint3)((uint)iVar1 >> 10),
                           (byte)iVar1 | ((byte)((ushort)sVar3 >> 8) & 7) >> 1) | 0x40000000;
    sVar3 = 0x1f;
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
    DAT_00ff6127 = DAT_00ff6127 + 1;
    if (6 < DAT_00ff6127) {
      DAT_00ff6127 = 0;
    }
  }
  return;
}

