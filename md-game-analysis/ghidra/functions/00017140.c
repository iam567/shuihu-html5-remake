/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00017140 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00017140(void)

{
  short sVar1;
  char cVar2;
  char *pcVar3;
  
  cVar2 = '\0';
  pcVar3 = (char *)&DAT_00ffe780;
  sVar1 = 0xb;
  while ((*pcVar3 == '\0' || (_DAT_00ffe1f0 != *(int *)(pcVar3 + 2)))) {
    cVar2 = cVar2 + '\x01';
    pcVar3 = pcVar3 + 0x40;
    sVar1 = sVar1 + -1;
    if (sVar1 == -1) {
      return;
    }
  }
  DAT_00ff606b = cVar2;
  FUN_0001717e();
  return;
}

