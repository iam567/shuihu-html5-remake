/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00019bfe */

void FUN_00019bfe(void)

{
  short sVar1;
  char extraout_D1b;
  char extraout_D1b_00;
  char extraout_D1b_01;
  char cVar2;
  short sVar3;
  
  if (DAT_00ff6177 == '\0') {
    FUN_0000b7fe();
    FUN_00019dc0();
    cVar2 = extraout_D1b;
  }
  else if (DAT_00ff6177 == '\x01') {
    FUN_0000b7fe();
    FUN_00019dc0();
    cVar2 = extraout_D1b_00;
  }
  else {
    FUN_0000b7fe();
    FUN_00019dc0();
    cVar2 = extraout_D1b_01;
  }
  if (cVar2 == '\0') {
    Seed_1060();
  }
  else {
    sVar1 = 0x7e;
    sVar3 = 0;
    do {
      if (((&DAT_00ffe400)[sVar3] == '\0') || (cVar2 == (&DAT_00ffe400)[sVar3])) break;
      sVar3 = sVar3 + 1;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    DAT_00ff617b = (undefined1)sVar3;
    FUN_00019cf6();
  }
  return;
}

