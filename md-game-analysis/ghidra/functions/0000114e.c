/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000114e */

void FUN_0000114e(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  char cVar4;
  short sVar5;
  short *psVar6;
  short *psVar7;
  short *psVar8;
  
  DAT_00ff6002 = 0xff;
  psVar7 = &DAT_00fff000;
  psVar6 = &DAT_00ff0000;
  sVar5 = DAT_00ff6012 + -1;
  if (DAT_00ff6012 != 0) {
    cVar4 = '\x01';
    do {
      uVar1 = psVar6[2];
      if (uVar1 == 0) break;
      psVar8 = *(short **)(&DAT_00028188 + (short)((uVar1 & 0x1fff) << 2)) + 1;
      sVar3 = **(short **)(&DAT_00028188 + (short)((uVar1 & 0x1fff) << 2));
      do {
        *psVar7 = psVar6[1] + *psVar8;
        psVar7[3] = *psVar6 + psVar8[3];
        psVar7[1] = CONCAT11((char)((ushort)psVar8[1] >> 8),cVar4);
        uVar2 = uVar1 & 0x8000 | psVar8[2];
        if ((uVar1 & 0x6000) != 0) {
          uVar2 = uVar1 & 0x6000 | uVar2;
        }
        psVar7[2] = uVar2;
        psVar7 = psVar7 + 4;
        cVar4 = cVar4 + '\x01';
        if (cVar4 == 'P') {
          return;
        }
        psVar8 = psVar8 + 4;
        sVar3 = sVar3 + -1;
      } while (sVar3 != -1);
      psVar6 = psVar6 + 3;
      sVar5 = sVar5 + -1;
    } while (sVar5 != -1);
    psVar7[0] = 0;
    psVar7[1] = 0;
    psVar7[2] = 0;
    psVar7[3] = 0;
  }
  return;
}

