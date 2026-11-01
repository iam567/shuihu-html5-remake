/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00024c1a */

undefined4 FUN_00024c1a(void)

{
  short sVar1;
  short sVar2;
  undefined4 in_D0;
  short sVar3;
  short extraout_D1w;
  short unaff_D3w;
  int extraout_A1;
  short *psVar4;
  short *psVar5;
  
  psVar4 = &DAT_00014200;
  sVar3 = 0x28;
  while( true ) {
    psVar5 = psVar4 + 1;
    sVar1 = *psVar4 + (DAT_00ffe780._2_2_ >> 5);
    psVar4 = psVar4 + 2;
    sVar2 = *psVar5 + (DAT_00ffe784._0_2_ >> 5);
    if ((((-1 < sVar1) && ((char)sVar1 < DAT_00ffe108)) && (-1 < sVar2)) &&
       ((((char)sVar2 < DAT_00ffe109 &&
         (sVar3 = FUN_00006902(), *(char *)(extraout_A1 + unaff_D3w) != '\x7f')) &&
        ((byte)(&DAT_00ffd000)[unaff_D3w] < 0x50)))) break;
    sVar3 = sVar3 + -1;
    if (sVar3 == -1) {
      return in_D0;
    }
  }
  DAT_00ff613a = extraout_D1w << 5;
  DAT_00ff613c = sVar2 * 0x20;
  return in_D0;
}

