/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003386 */

char FUN_00003386(void)

{
  char cVar1;
  short sVar2;
  
  sVar2 = 9;
  do {
    FUN_00002e5a();
    cVar1 = FUN_00003142();
    cVar1 = cVar1 + '\x04';
    if (cVar1 == '@') {
      cVar1 = '\0';
    }
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return cVar1;
}

