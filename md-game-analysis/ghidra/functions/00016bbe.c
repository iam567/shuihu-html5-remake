/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00016bbe */

void FUN_00016bbe(void)

{
  short sVar1;
  undefined2 *unaff_A2;
  undefined2 *puVar2;
  undefined2 *puVar3;
  
  if (DAT_00ff6312 != '\0') {
    puVar2 = &DAT_00ff6328;
    sVar1 = 1;
    do {
      puVar3 = puVar2 + 1;
      *unaff_A2 = *puVar2;
      puVar2 = puVar2 + 2;
      unaff_A2[1] = *puVar3;
      unaff_A2[2] = (DAT_00ff6010 & 1) + 0x49;
      unaff_A2 = unaff_A2 + 3;
      DAT_00ff6012 = DAT_00ff6012 + 1;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
  }
  return;
}

