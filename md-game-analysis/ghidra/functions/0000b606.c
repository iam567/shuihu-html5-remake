/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000b606 */

void FUN_0000b606(void)

{
  short sVar1;
  char *pcVar2;
  
  FUN_00009df8();
  FUN_00002846();
  DAT_00ff60b7 = 0;
  DAT_00ff60b8 = '\0';
  pcVar2 = &DAT_00ffe7a6 + (short)((ushort)DAT_00ff606b << 6);
  sVar1 = 3;
  do {
    if (*pcVar2 != '\0') {
      DAT_00ff60b8 = DAT_00ff60b8 + '\x01';
    }
    pcVar2 = pcVar2 + 1;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  FUN_00006f50();
  DAT_00ff60b4 = 0x1001;
  DAT_00ff60b6 = 0x22;
  FUN_0000b78a();
  FUN_0000bdfc();
  return;
}

