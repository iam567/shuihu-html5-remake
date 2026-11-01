/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001b6e8 */

void FUN_0001b6e8(void)

{
  uint uVar1;
  short sVar2;
  undefined1 *puVar3;
  char *pcVar4;
  
  puVar3 = &DAT_00ff9000;
  if ((DAT_00ff6188 & 1) != 0) {
    puVar3 = &DAT_00ffe400;
  }
  uVar1 = *(uint *)(&DAT_0001a130 + (short)((ushort)(byte)puVar3[(short)(ushort)DAT_00ff617a] << 2))
  ;
  pcVar4 = &DAT_00ff8000;
  sVar2 = 0x13;
  do {
    if (*pcVar4 == '\0') {
      return;
    }
    pcVar4[0x1d] = '\x01';
    if ((uVar1 & 1 << ((byte)(pcVar4[0x24] - 1) & 0x1f)) != 0) {
      pcVar4[0x1d] = '\0';
    }
    pcVar4 = pcVar4 + 0x40;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}

