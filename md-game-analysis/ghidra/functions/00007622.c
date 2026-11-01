/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007622 */

void Seed_7622(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  int iVar6;
  
  puVar4 = &DAT_00007650;
  iVar6 = 0xffe000;
  sVar1 = 0xf;
  do {
    sVar2 = 0;
    sVar3 = 3;
    puVar5 = puVar4;
    do {
      puVar4 = puVar5 + 1;
      *(undefined2 *)(iVar6 + sVar2) = *puVar5;
      sVar2 = sVar2 + 2;
      sVar3 = sVar3 + -1;
      puVar5 = puVar4;
    } while (sVar3 != -1);
    iVar6 = iVar6 + 0x10;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}

