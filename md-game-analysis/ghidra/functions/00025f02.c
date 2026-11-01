/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00025f02 */

void FUN_00025f02(void)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  short sVar4;
  uint uVar5;
  short sVar6;
  short *unaff_A2;
  
  uVar3 = DAT_00ffe11c;
  uVar5 = 0;
  sVar4 = 0x1f;
  do {
    if (((uVar3 & 1 << (uVar5 & 0x1f)) != 0) &&
       (sVar6 = (short)uVar5 << 3, *(short *)((int)&DAT_00025f86 + (int)sVar6) == DAT_00ffe100)) {
      sVar1 = (*(short *)((int)&DAT_00025f88 + (int)sVar6) - DAT_00ff6014) + 0x80;
      sVar2 = (*(short *)((int)&DAT_00025f8a + (int)sVar6) - DAT_00ff6016) + 0x80;
      if ((0x3f < sVar1) && (((0x3f < sVar2 && (sVar1 < 0x1c1)) && (sVar2 < 0x171)))) {
        *unaff_A2 = sVar1;
        unaff_A2[1] = sVar2;
        unaff_A2[2] = *(short *)((int)&DAT_00025f8c + (int)sVar6);
        DAT_00ff6012 = DAT_00ff6012 + 1;
        unaff_A2 = unaff_A2 + 3;
      }
    }
    uVar5 = (uint)(byte)((char)uVar5 + 1);
    sVar4 = sVar4 + -1;
  } while (sVar4 != -1);
  return;
}

