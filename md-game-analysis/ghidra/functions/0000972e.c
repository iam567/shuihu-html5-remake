/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000972e */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0000972e(void)

{
  short sVar1;
  short unaff_D3w;
  char cVar2;
  short *psVar3;
  short *extraout_A0;
  int extraout_A1;
  
  FUN_00009778();
  psVar3 = (short *)&DAT_00ff1000;
  cVar2 = '\x7f';
  while (sVar1 = *psVar3, sVar1 != -1) {
    FUN_00006902();
    psVar3 = extraout_A0;
    if ((*(char *)(extraout_A1 + unaff_D3w) != -1) && (*(char *)(extraout_A1 + unaff_D3w) < cVar2))
    {
      cVar2 = *(char *)(extraout_A1 + unaff_D3w);
      _DAT_00ff6062 = sVar1;
    }
  }
  return;
}

