/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009516 */

void FUN_00009516(void)

{
  byte bVar1;
  short unaff_D3w;
  bool bVar2;
  int extraout_A1;
  int extraout_A1_00;
  int extraout_A1_01;
  int extraout_A1_02;
  int unaff_A2;
  short *psVar3;
  short *psVar5;
  short *psVar4;
  
  DAT_00ff60c0._0_1_ = (&DAT_00006c68)[(short)(ushort)(byte)(*(char *)(unaff_A2 + 0x24) - 1)];
  if (*(char *)(unaff_A2 + 0x2a) == 'w') {
    DAT_00ff60c0._0_1_ = 0x6f;
  }
  else if (*(char *)(unaff_A2 + 0x2a) == 'x') {
    DAT_00ff60c0._0_1_ = 0x5f;
  }
  DAT_00ff605c = CONCAT11(DAT_00ff6088,DAT_00ff6089);
  FUN_000068e2();
  *(undefined1 *)((int)&DAT_00ff2000 + (int)unaff_D3w) = 0;
  DAT_00ff3000._0_2_ = DAT_00ff605c;
  DAT_00ff3000._2_2_ = 0xffff;
  DAT_00ff6060 = 1;
  while( true ) {
    psVar5 = (short *)&DAT_00ff3000;
    psVar3 = (short *)&DAT_00ff4000;
    if ((DAT_00ff6060 & 1) != 0) {
      psVar5 = (short *)&DAT_00ff4000;
      DAT_00ff6061 = '\0';
      psVar3 = (short *)&DAT_00ff3000;
    }
    while( true ) {
      psVar4 = psVar3 + 1;
      if (*psVar3 == -1) break;
      DAT_00ff6061 = DAT_00ff6061 + '\x01';
      bVar2 = false;
      DAT_00ff605c = *psVar3;
      do {
        psVar3 = psVar5;
        if ((((char)DAT_00ff605c != '\0') &&
            (bVar1 = FUN_00006902(), (byte)(&DAT_00ffd000)[unaff_D3w] < bVar1)) &&
           (bVar2 = true, *(char *)(extraout_A1 + unaff_D3w) == -1)) {
          *(byte *)(extraout_A1 + unaff_D3w) = DAT_00ff6060;
          psVar3 = psVar5 + 1;
          *psVar5 = DAT_00ff605c + -1;
        }
        psVar5 = psVar3;
        if (((DAT_00ff605c._0_1_ != '\0') &&
            (bVar1 = FUN_00006902(), (byte)(&DAT_00ffd000)[unaff_D3w] < bVar1)) &&
           (bVar2 = true, *(char *)(extraout_A1_00 + unaff_D3w) == -1)) {
          *(byte *)(extraout_A1_00 + unaff_D3w) = DAT_00ff6060;
          psVar5 = psVar3 + 1;
          *psVar3 = DAT_00ff605c + -0x100;
        }
        psVar3 = psVar5;
        if ((((char)((char)DAT_00ff605c + '\x01') < DAT_00ffe109) &&
            (bVar1 = FUN_00006902(), (byte)(&DAT_00ffd000)[unaff_D3w] < bVar1)) &&
           (bVar2 = true, *(char *)(extraout_A1_01 + unaff_D3w) == -1)) {
          *(byte *)(extraout_A1_01 + unaff_D3w) = DAT_00ff6060;
          psVar3 = psVar5 + 1;
          *psVar5 = DAT_00ff605c + 1;
        }
        psVar5 = psVar3;
        if ((((char)(DAT_00ff605c._0_1_ + '\x01') < DAT_00ffe108) &&
            (bVar1 = FUN_00006902(), (byte)(&DAT_00ffd000)[unaff_D3w] < bVar1)) &&
           (bVar2 = true, *(char *)(extraout_A1_02 + unaff_D3w) == -1)) {
          *(byte *)(extraout_A1_02 + unaff_D3w) = DAT_00ff6060;
          psVar5 = psVar3 + 1;
          *psVar3 = DAT_00ff605c + 0x100;
        }
        psVar3 = psVar4;
      } while (!bVar2);
    }
    if (DAT_00ff6061 == '\0') break;
    *psVar5 = -1;
    DAT_00ff6060 = DAT_00ff6060 + 1;
  }
  return;
}

