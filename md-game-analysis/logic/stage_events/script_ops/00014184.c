/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00014184 */

void FUN_00014184(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined2 extraout_D1w;
  short unaff_D3w;
  int extraout_A1;
  short *psVar4;
  short *psVar5;
  
  psVar4 = &DAT_00014200;
  sVar3 = 0x28;
  while( true ) {
    psVar5 = psVar4 + 1;
    sVar1 = *psVar4;
    psVar4 = psVar4 + 2;
    sVar2 = *psVar5 + DAT_00ff613c;
    if ((((-1 < (short)(sVar1 + DAT_00ff613a)) && ((char)(sVar1 + DAT_00ff613a) < DAT_00ffe108)) &&
        (-1 < sVar2)) &&
       ((((char)sVar2 < DAT_00ffe109 &&
         (sVar3 = FUN_00006902(), *(char *)(extraout_A1 + unaff_D3w) != '\x7f')) &&
        ((byte)(&DAT_00ffd000)[unaff_D3w] < 0x50)))) break;
    sVar3 = sVar3 + -1;
    if (sVar3 == -1) {
      return;
    }
  }
  DAT_00ff613a = extraout_D1w;
  DAT_00ff613c = sVar2;
  return;
}

