/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d59c */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0000d59c(void)

{
  short sVar1;
  short unaff_D3w;
  char cVar2;
  short *psVar3;
  short *extraout_A0;
  int extraout_A1;
  
  FUN_00009778();
  FUN_0000d5fa();
  psVar3 = (short *)&DAT_00ff1000;
  cVar2 = '\0';
  while (sVar1 = *psVar3, sVar1 != -1) {
    FUN_00006902();
    psVar3 = extraout_A0;
    if (((*(char *)(extraout_A1 + unaff_D3w) != -1) && ((&DAT_00ff5000)[unaff_D3w] != '\0')) &&
       (cVar2 < *(char *)(extraout_A1 + unaff_D3w))) {
      cVar2 = *(char *)(extraout_A1 + unaff_D3w);
      _DAT_00ff6062 = sVar1;
    }
  }
  return;
}

