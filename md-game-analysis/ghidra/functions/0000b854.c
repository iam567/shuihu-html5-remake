/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000b854 */

void FUN_0000b854(void)

{
  short sVar1;
  char *pcVar2;
  
  FUN_00009df8();
  DAT_00ff60b7 = 0;
  DAT_00ff60b8 = '\0';
  pcVar2 = (char *)((int)&DAT_00ffe788 + (int)(short)((ushort)DAT_00ff606b << 6));
  sVar1 = 3;
  do {
    if (*pcVar2 != '\0') {
      DAT_00ff60b8 = DAT_00ff60b8 + '\x01';
    }
    pcVar2 = pcVar2 + 1;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  FUN_00001098();
  FUN_00006f50();
  FUN_0000b8d0();
  FUN_0000b93c();
  return;
}

