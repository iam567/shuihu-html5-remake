/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006a08 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00006a08(void)

{
  short sVar1;
  byte bVar2;
  short unaff_D3w;
  short *in_A1;
  short *psVar3;
  short *extraout_A1;
  short *extraout_A1_00;
  short *extraout_A1_01;
  short *extraout_A1_02;
  short *extraout_A1_03;
  int unaff_A3;
  int unaff_A4;
  short *psVar4;
  short *psVar6;
  short *psVar7;
  short *psVar5;
  
  *(undefined1 *)(unaff_A3 + unaff_D3w) = DAT_00ff60bf;
  *(undefined1 *)(unaff_D3w + 0xff8000) = 0;
  _DAT_00ff9000 = DAT_00ff605c;
  DAT_00ff9002 = 0xffff;
  psVar3 = in_A1 + 1;
  *in_A1 = DAT_00ff605c;
  while( true ) {
    psVar4 = (short *)&DAT_00ff9000;
    psVar6 = &DAT_00ffa000;
    if ((DAT_00ff6060 & 1) != 0) {
      DAT_00ff6061 = '\0';
      psVar4 = &DAT_00ffa000;
      psVar6 = (short *)&DAT_00ff9000;
    }
    while( true ) {
      psVar5 = psVar4 + 1;
      if (*psVar4 == -1) break;
      DAT_00ff605c = *psVar4;
      FUN_000068e2();
      DAT_00ff605e = *(char *)(unaff_A3 + unaff_D3w);
      DAT_00ff6061 = DAT_00ff6061 + '\x01';
      psVar3 = extraout_A1;
      psVar4 = psVar6;
      if ((char)DAT_00ff605c != '\0') {
        bVar2 = FUN_00006902();
        psVar3 = extraout_A1_00;
        if ((((*(byte *)(unaff_A4 + unaff_D3w) < bVar2) && (DAT_00ff605e != '\0')) &&
            ((*(char *)(unaff_A3 + unaff_D3w) == -1 ||
             (*(char *)(unaff_A3 + unaff_D3w) < (char)(DAT_00ff605e + -1))))) &&
           (*(char *)(unaff_A3 + unaff_D3w) = DAT_00ff605e + -1,
           DAT_00ff6060 != *(byte *)(unaff_D3w + 0xff8000))) {
          *(byte *)(unaff_D3w + 0xff8000) = DAT_00ff6060;
          sVar1 = DAT_00ff605c + -1;
          psVar4 = psVar6 + 1;
          *psVar6 = sVar1;
          psVar3 = extraout_A1_00 + 1;
          *extraout_A1_00 = sVar1;
        }
      }
      psVar6 = psVar4;
      if (DAT_00ff605c._0_1_ != '\0') {
        bVar2 = FUN_00006902();
        psVar3 = extraout_A1_01;
        if (((*(byte *)(unaff_A4 + unaff_D3w) < bVar2) && (DAT_00ff605e != '\0')) &&
           (((*(char *)(unaff_A3 + unaff_D3w) == -1 ||
             (*(char *)(unaff_A3 + unaff_D3w) < (char)(DAT_00ff605e + -1))) &&
            (*(char *)(unaff_A3 + unaff_D3w) = DAT_00ff605e + -1,
            DAT_00ff6060 != *(byte *)(unaff_D3w + 0xff8000))))) {
          *(byte *)(unaff_D3w + 0xff8000) = DAT_00ff6060;
          sVar1 = DAT_00ff605c + -0x100;
          psVar6 = psVar4 + 1;
          *psVar4 = sVar1;
          psVar3 = extraout_A1_01 + 1;
          *extraout_A1_01 = sVar1;
        }
      }
      psVar7 = psVar6;
      if ((char)((char)DAT_00ff605c + '\x01') < DAT_00ffe109) {
        bVar2 = FUN_00006902();
        psVar3 = extraout_A1_02;
        if ((((*(byte *)(unaff_A4 + unaff_D3w) < bVar2) && (DAT_00ff605e != '\0')) &&
            ((*(char *)(unaff_A3 + unaff_D3w) == -1 ||
             (*(char *)(unaff_A3 + unaff_D3w) < (char)(DAT_00ff605e + -1))))) &&
           (*(char *)(unaff_A3 + unaff_D3w) = DAT_00ff605e + -1,
           DAT_00ff6060 != *(byte *)(unaff_D3w + 0xff8000))) {
          *(byte *)(unaff_D3w + 0xff8000) = DAT_00ff6060;
          sVar1 = DAT_00ff605c + 1;
          psVar7 = psVar6 + 1;
          *psVar6 = sVar1;
          psVar3 = extraout_A1_02 + 1;
          *extraout_A1_02 = sVar1;
        }
      }
      psVar4 = psVar5;
      psVar6 = psVar7;
      if ((char)(DAT_00ff605c._0_1_ + '\x01') < DAT_00ffe108) {
        bVar2 = FUN_00006902();
        psVar3 = extraout_A1_03;
        if (((*(byte *)(unaff_A4 + unaff_D3w) < bVar2) && (DAT_00ff605e != '\0')) &&
           (((*(char *)(unaff_A3 + unaff_D3w) == -1 ||
             (*(char *)(unaff_A3 + unaff_D3w) < (char)(DAT_00ff605e + -1))) &&
            (*(char *)(unaff_A3 + unaff_D3w) = DAT_00ff605e + -1,
            DAT_00ff6060 != *(byte *)(unaff_D3w + 0xff8000))))) {
          *(byte *)(unaff_D3w + 0xff8000) = DAT_00ff6060;
          sVar1 = DAT_00ff605c + 0x100;
          psVar6 = psVar7 + 1;
          *psVar7 = sVar1;
          psVar3 = extraout_A1_03 + 1;
          *extraout_A1_03 = sVar1;
        }
      }
    }
    if (DAT_00ff6061 == '\0') break;
    *psVar6 = -1;
    DAT_00ff6060 = DAT_00ff6060 + 1;
  }
  *psVar3 = -1;
  return;
}

