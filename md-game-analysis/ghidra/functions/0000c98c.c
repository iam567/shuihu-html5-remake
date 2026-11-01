/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000c98c */

void FUN_0000c98c(void)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  
  if ((char)DAT_00ff606b < '\x1d') {
    pcVar3 = (char *)((int)&DAT_00ffe780 + (int)(short)((ushort)DAT_00ff606b << 6));
    bVar2 = DAT_00ff606b;
    while( true ) {
      if (*pcVar3 != '\0') {
        cVar1 = pcVar3[0xc];
        pcVar3[0xc] = cVar1 + -1;
        if (cVar1 == '\0') {
          pcVar3[0xc] = '\0';
        }
        cVar1 = pcVar3[0xe];
        pcVar3[0xe] = cVar1 + -1;
        if (cVar1 == '\0') {
          pcVar3[0xe] = '\0';
        }
        cVar1 = pcVar3[0xf];
        pcVar3[0xf] = cVar1 + -1;
        if (cVar1 == '\0') {
          pcVar3[0xf] = '\0';
        }
        if (pcVar3[0xd] != '\0') {
          DAT_00ff606b = bVar2;
          FUN_00007c14();
          DAT_00ff6106 = 1;
          return;
        }
      }
      bVar2 = bVar2 + 1;
      if ('\x1d' < (char)bVar2) break;
      pcVar3 = pcVar3 + 0x40;
    }
  }
  DAT_00ff6105 = 0;
  FUN_00008c8a();
  return;
}

