/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000103ce */

void FUN_000103ce(void)

{
  short sVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 unaff_A3;
  
  puVar3 = &DAT_00ffe780;
  cVar2 = '\0';
  sVar1 = 0x1d;
  do {
    if (*(char *)((int)puVar3 + 0x2f) != '\0') {
      DAT_00ff6130 = unaff_A3;
      *(undefined1 *)((int)puVar3 + 0x2f) = 0;
      DAT_00ff6150 = cVar2;
      DAT_00ff6158 = 1;
      return;
    }
    cVar2 = cVar2 + '\x01';
    puVar3 = puVar3 + 0x10;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00ff6159 = 0;
  DAT_00ff6158 = 0;
  DAT_00ff6130 = unaff_A3;
  return;
}

