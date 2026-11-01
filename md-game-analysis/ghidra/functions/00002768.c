/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00002768 */

void FUN_00002768(void)

{
  ushort uVar1;
  uint uVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  uint unaff_A2;
  char *pcVar6;
  
  uVar2 = ~DAT_00ff6080;
  DAT_00ff6080 = 0;
  sVar3 = 3;
  uVar1 = DAT_00ff6010 & 7;
  uVar5 = (uint)(byte)uVar1;
  pcVar6 = (char *)((int)&DAT_00ffe780 + (int)(short)(uVar1 << 6));
  iVar4 = (uint)uVar1 * 0x2000000 + 0x44000080;
  do {
    if (((uVar2 & 0x3fffffff & 1 << (uVar5 & 0x1f)) != 0) && (*pcVar6 != '\0')) {
      sVar3 = FUN_00002820();
      Ram00c00004 = 0x9300;
      Ram00c00004 = 0x9401;
      Ram00c00004 = CONCAT11(0x95,(char)(unaff_A2 >> 1));
      Ram00c00004 = CONCAT11(0x96,(char)((unaff_A2 >> 1) >> 8));
      Ram00c00004 = CONCAT11(0x97,(char)((unaff_A2 >> 9) >> 8));
      Ram00c00004 = iVar4;
    }
    iVar4 = iVar4 + 0x10000000;
    pcVar6 = pcVar6 + 0x200;
    uVar1 = (short)uVar5 + 8;
    uVar5 = (uint)uVar1;
  } while (((short)uVar1 < 0x1e) && (sVar3 = sVar3 + -1, sVar3 != -1));
  return;
}

