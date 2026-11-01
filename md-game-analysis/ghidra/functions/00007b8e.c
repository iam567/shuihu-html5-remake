/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007b8e */

void FUN_00007b8e(void)

{
  uint uVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  uint unaff_A2;
  char *pcVar5;
  
  uVar1 = DAT_00ff6080;
  pcVar5 = (char *)&DAT_00ffe780;
  uVar4 = 0;
  iVar3 = 0x44000080;
  sVar2 = 0x1d;
  do {
    if (((uVar1 & 1 << (uVar4 & 0x1f)) != 0) && (*pcVar5 != '\0')) {
      sVar2 = FUN_00002820();
      Ram00c00004 = 0x9300;
      Ram00c00004 = 0x9401;
      Ram00c00004 = CONCAT11(0x95,(char)(unaff_A2 >> 1));
      Ram00c00004 = CONCAT11(0x96,(char)((unaff_A2 >> 1) >> 8));
      Ram00c00004 = CONCAT11(0x97,(char)((unaff_A2 >> 9) >> 8));
      Ram00c00004 = iVar3;
    }
    iVar3 = iVar3 + 0x2000000;
    pcVar5 = pcVar5 + 0x40;
    uVar4 = (uint)(ushort)((short)uVar4 + 1);
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}

