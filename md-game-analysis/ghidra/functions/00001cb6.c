/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00001cb6 */

void FUN_00001cb6(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  short *unaff_A2;
  char *pcVar7;
  
  pcVar7 = &DAT_00ffe000;
  uVar5 = 0;
  uVar6 = 0;
  sVar3 = 7;
  do {
    if (((*pcVar7 != '\0') &&
        ((((DAT_00ff601d & '\x01' << (uVar5 >> 2 & 7)) == 0 || ((DAT_00ff6010 & 1) != 0)) &&
         (sVar1 = *(short *)(pcVar7 + 2) - DAT_00ff6014, sVar1 < 0x141)))) && (-0x21 < sVar1)) {
      sVar2 = *(short *)(pcVar7 + 4) - DAT_00ff6016;
      if ((sVar2 < 0xf1) && (-0x21 < sVar2)) {
        *unaff_A2 = sVar1 + 0x80;
        unaff_A2[1] = sVar2 + 0x80;
        uVar4 = *(ushort *)
                 (*(int *)((int)&DAT_00001d6e + (int)(short)uVar5) +
                 (int)(short)((ushort)(byte)pcVar7[1] << 1));
        if ((DAT_00ff611f & '\x01' << (uVar6 & 7)) != 0) {
          uVar4 = uVar4 | 0x6000;
        }
        unaff_A2[2] = uVar4;
        DAT_00ff6012 = DAT_00ff6012 + 1;
        unaff_A2 = unaff_A2 + 3;
      }
    }
    uVar6 = (uint)(byte)((char)uVar6 + 1);
    uVar5 = uVar5 + 4;
    pcVar7 = pcVar7 + 0x10;
    sVar3 = sVar3 + -1;
  } while (sVar3 != -1);
  return;
}

