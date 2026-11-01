/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000c006 */

void FUN_0000c006(void)

{
  short sVar1;
  char *pcVar2;
  
  pcVar2 = (char *)&DAT_00ffe780;
  sVar1 = 0x1d;
  do {
    if ((((*pcVar2 != '\0') && (-0x14 < (short)(*(short *)(pcVar2 + 2) - DAT_00ff6014))) &&
        ((short)(*(short *)(pcVar2 + 2) - DAT_00ff6014) < 0x140)) &&
       ((-0x14 < (short)(*(short *)(pcVar2 + 4) - DAT_00ff6016) &&
        ((short)(*(short *)(pcVar2 + 4) - DAT_00ff6016) < 0xe0)))) {
      FUN_00006f50();
    }
    pcVar2 = pcVar2 + 0x40;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}

