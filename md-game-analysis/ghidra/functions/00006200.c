/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006200 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00006200(void)

{
  short sVar1;
  char *pcVar2;
  
  pcVar2 = (char *)&DAT_00ffe780;
  sVar1 = 0x1d;
  while ((*pcVar2 == '\0' || (*(int *)(pcVar2 + 2) != _DAT_00ffe1f0))) {
    pcVar2 = pcVar2 + 0x40;
    sVar1 = sVar1 + -1;
    if (sVar1 == -1) {
      return;
    }
  }
  return;
}

