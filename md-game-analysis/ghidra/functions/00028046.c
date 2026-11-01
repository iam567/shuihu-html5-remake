/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00028046 */

void FUN_00028046(void)

{
  byte bVar1;
  short sVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  Ram00a11100 = 0x100;
  Ram00a11200 = 0x100;
  do {
    bVar1 = DAT_00a11100;
  } while ((bVar1 & 1) != 0);
  sVar2 = 0x25;
  puVar3 = &DAT_000280ae;
  puVar4 = &DAT_00a00000;
  do {
    *puVar4 = *puVar3;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  } while (sVar2 != -1);
  Ram00a11200 = 0;
  Ram00a11200 = 0x100;
  Ram00a11100 = 0;
  return;
}

