/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000099fa */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000099fa(void)

{
  short sVar1;
  char cVar2;
  short unaff_D3w;
  char cVar3;
  short *psVar4;
  short *extraout_A0;
  int extraout_A1;
  
  FUN_00009a6c();
  FUN_00009778();
  FUN_00009ad6();
  psVar4 = (short *)&DAT_00ff1000;
  cVar3 = '\0';
  while (sVar1 = *psVar4, sVar1 != -1) {
    FUN_00006902();
    psVar4 = extraout_A0;
    if (((*(char *)(extraout_A1 + unaff_D3w) != -1) && ((&DAT_00ff5000)[unaff_D3w] != '\0')) &&
       (cVar2 = (&DAT_00ff1800)[unaff_D3w] + *(char *)(extraout_A1 + unaff_D3w) + '\x14',
       cVar3 < cVar2)) {
      cVar3 = cVar2;
      _DAT_00ff6062 = sVar1;
    }
  }
  return;
}

