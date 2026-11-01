/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006986 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00006986(void)

{
  short sVar1;
  int iVar2;
  byte bVar3;
  short unaff_D3w;
  short *extraout_A1;
  short *psVar4;
  short *extraout_A1_00;
  short *extraout_A1_01;
  short *extraout_A1_02;
  short *extraout_A1_03;
  short *extraout_A1_04;
  short *psVar5;
  short *psVar7;
  short *psVar8;
  short *psVar6;
  
  iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
  DAT_00ff605c = CONCAT11((char)(*(ushort *)((int)&DAT_00ffe780 + iVar2 + 2) >> 5),
                          (char)(*(ushort *)((int)&DAT_00ffe784 + iVar2) >> 5));
  DAT_00ff60bf = (&DAT_00ffe79b)[iVar2];
  DAT_00ff6060 = 0;
  FUN_000068e2();
  *(undefined1 *)((int)&DAT_00ffb000 + (int)unaff_D3w) = DAT_00ff60bf;
  *(undefined1 *)(unaff_D3w + 0xff8000) = 0;
  _DAT_00ff9000 = DAT_00ff605c;
  DAT_00ff9002 = 0xffff;
  psVar4 = extraout_A1 + 1;
  *extraout_A1 = DAT_00ff605c;
  while( true ) {
    psVar5 = (short *)&DAT_00ff9000;
    psVar7 = &DAT_00ffa000;
    if ((DAT_00ff6060 & 1) != 0) {
      DAT_00ff6061 = '\0';
      psVar5 = &DAT_00ffa000;
      psVar7 = (short *)&DAT_00ff9000;
    }
    while( true ) {
      psVar6 = psVar5 + 1;
      if (*psVar5 == -1) break;
      DAT_00ff605c = *psVar5;
      FUN_000068e2();
      DAT_00ff605e = *(char *)((int)&DAT_00ffb000 + (int)unaff_D3w);
      DAT_00ff6061 = DAT_00ff6061 + '\x01';
      psVar4 = extraout_A1_00;
      psVar5 = psVar7;
      if (((((char)DAT_00ff605c != '\0') &&
           (bVar3 = FUN_00006902(), psVar4 = extraout_A1_01,
           (byte)(&DAT_00ffd000)[unaff_D3w] < bVar3)) && (DAT_00ff605e != '\0')) &&
         (((*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) == -1 ||
           (*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) < (char)(DAT_00ff605e + -1))) &&
          (*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) = DAT_00ff605e + -1,
          DAT_00ff6060 != *(byte *)(unaff_D3w + 0xff8000))))) {
        *(byte *)(unaff_D3w + 0xff8000) = DAT_00ff6060;
        sVar1 = DAT_00ff605c + -1;
        psVar5 = psVar7 + 1;
        *psVar7 = sVar1;
        psVar4 = extraout_A1_01 + 1;
        *extraout_A1_01 = sVar1;
      }
      psVar7 = psVar5;
      if (((DAT_00ff605c._0_1_ != '\0') &&
          (bVar3 = FUN_00006902(), psVar4 = extraout_A1_02, (byte)(&DAT_00ffd000)[unaff_D3w] < bVar3
          )) && ((DAT_00ff605e != '\0' &&
                 (((*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) == -1 ||
                   (*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) < (char)(DAT_00ff605e + -1))) &&
                  (*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) = DAT_00ff605e + -1,
                  DAT_00ff6060 != *(byte *)(unaff_D3w + 0xff8000))))))) {
        *(byte *)(unaff_D3w + 0xff8000) = DAT_00ff6060;
        sVar1 = DAT_00ff605c + -0x100;
        psVar7 = psVar5 + 1;
        *psVar5 = sVar1;
        psVar4 = extraout_A1_02 + 1;
        *extraout_A1_02 = sVar1;
      }
      psVar8 = psVar7;
      if ((((char)((char)DAT_00ff605c + '\x01') < DAT_00ffe109) &&
          (bVar3 = FUN_00006902(), psVar4 = extraout_A1_03, (byte)(&DAT_00ffd000)[unaff_D3w] < bVar3
          )) && (((DAT_00ff605e != '\0' &&
                  ((*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) == -1 ||
                   (*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) < (char)(DAT_00ff605e + -1)))))
                 && (*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) = DAT_00ff605e + -1,
                    DAT_00ff6060 != *(byte *)(unaff_D3w + 0xff8000))))) {
        *(byte *)(unaff_D3w + 0xff8000) = DAT_00ff6060;
        sVar1 = DAT_00ff605c + 1;
        psVar8 = psVar7 + 1;
        *psVar7 = sVar1;
        psVar4 = extraout_A1_03 + 1;
        *extraout_A1_03 = sVar1;
      }
      psVar5 = psVar6;
      psVar7 = psVar8;
      if ((((((char)(DAT_00ff605c._0_1_ + '\x01') < DAT_00ffe108) &&
            (bVar3 = FUN_00006902(), psVar4 = extraout_A1_04,
            (byte)(&DAT_00ffd000)[unaff_D3w] < bVar3)) && (DAT_00ff605e != '\0')) &&
          ((*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) == -1 ||
           (*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) < (char)(DAT_00ff605e + -1))))) &&
         (*(char *)((int)&DAT_00ffb000 + (int)unaff_D3w) = DAT_00ff605e + -1,
         DAT_00ff6060 != *(byte *)(unaff_D3w + 0xff8000))) {
        *(byte *)(unaff_D3w + 0xff8000) = DAT_00ff6060;
        sVar1 = DAT_00ff605c + 0x100;
        psVar7 = psVar8 + 1;
        *psVar8 = sVar1;
        psVar4 = extraout_A1_04 + 1;
        *extraout_A1_04 = sVar1;
      }
    }
    if (DAT_00ff6061 == '\0') break;
    *psVar7 = -1;
    DAT_00ff6060 = DAT_00ff6060 + 1;
  }
  *psVar4 = -1;
  return;
}

