/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000c74c */

void FUN_0000c74c(void)

{
  char cVar1;
  ushort uVar2;
  char *pcVar3;
  
  uVar2 = (ushort)DAT_00ff606b;
  if ((short)uVar2 < DAT_00ffe1fa) {
    pcVar3 = (char *)((int)&DAT_00ffe780 + (int)(short)((ushort)DAT_00ff606b << 6));
    while( true ) {
      DAT_00ff606b = (byte)uVar2;
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
          FUN_00007c14();
          DAT_00ff6106 = 1;
          return;
        }
      }
      uVar2 = (ushort)(byte)(DAT_00ff606b + 1);
      if (DAT_00ffe1fa <= (short)uVar2) break;
      pcVar3 = pcVar3 + 0x40;
    }
  }
  DAT_00ff6104 = 0;
  DAT_00ff6036 = 1;
  DAT_00ff606b = 0;
  FUN_00007c14();
  return;
}

