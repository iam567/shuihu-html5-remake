/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006e92 */

char FUN_00006e92(void)

{
  char cVar1;
  short sVar2;
  byte *pbVar3;
  
  sVar2 = 9;
  pbVar3 = (byte *)((int)&DAT_00ffb000 +
                   (int)(short)(ushort)DAT_00ffe104 +
                   (uint)(byte)(DAT_00ffe105 + 6) * (uint)DAT_00ffe106);
  do {
    if (*pbVar3 < 0x7f) {
      cVar1 = FUN_0000309a();
    }
    else {
      cVar1 = FUN_0000353c();
    }
    cVar1 = cVar1 + '\x04';
    if (cVar1 == '@') {
      cVar1 = '\0';
    }
    sVar2 = sVar2 + -1;
    pbVar3 = pbVar3 + 1;
  } while (sVar2 != -1);
  return cVar1;
}

