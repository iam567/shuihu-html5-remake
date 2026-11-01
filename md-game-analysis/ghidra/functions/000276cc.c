/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000276cc */

void FUN_000276cc(void)

{
  short sVar1;
  undefined1 *puVar2;
  undefined2 *puVar3;
  undefined1 *puVar4;
  undefined2 *puVar5;
  
  sVar1 = 0x17;
  puVar2 = &DAT_000276f2;
  puVar3 = &DAT_0002770a;
  puVar4 = &DAT_00ff61c0;
  puVar5 = &DAT_00ff61d8;
  do {
    *puVar4 = *puVar2;
    *puVar5 = *puVar3;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  } while (sVar1 != -1);
  return;
}

