/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000280d4 */

void FUN_000280d4(void)

{
  char cVar1;
  undefined1 uVar2;
  byte bVar3;
  
  Ram00a11100 = 0x100;
  do {
    bVar3 = DAT_00a11100;
  } while ((bVar3 & 1) != 0);
  DAT_00ff6d04 = 0;
  DAT_00a04000 = 0x26;
  DAT_00a04001 = 0xff;
  do {
    cVar1 = DAT_00a04000;
    uVar2 = DAT_00a04000;
  } while (cVar1 < '\0');
  DAT_00a04000 = 0x27;
  DAT_00a04001 = 0x2f;
  do {
    cVar1 = DAT_00a04000;
    uVar2 = DAT_00a04000;
  } while (cVar1 < '\0');
  DAT_00a04000 = 0x2b;
  DAT_00a04001 = 0x80;
  do {
    cVar1 = DAT_00a04000;
    uVar2 = DAT_00a04000;
  } while (cVar1 < '\0');
  DAT_00a00020 = 0;
  DAT_00a00022 = 0;
  Ram00a11100 = 0;
  return;
}

