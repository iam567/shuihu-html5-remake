/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000248e2 */

void FUN_000248e2(void)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  char *pcVar4;
  
  DAT_00ff616c = 0;
  uVar3 = 0;
  sVar2 = DAT_00ffe115 - 1;
  do {
    pcVar4 = *(char **)(&DAT_00024962 + (short)((ushort)DAT_00ffe10f << 2));
    do {
      if (*pcVar4 == -1) goto LAB_00024922;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while ((&DAT_00ffe610)[(short)uVar3] != cVar1);
    DAT_00ff616c = DAT_00ff616c | 1 << (uVar3 & 0x1f);
LAB_00024922:
    uVar3 = (uint)(ushort)((short)uVar3 + 1);
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      DAT_00ff6170 = DAT_00ff616c;
      DAT_00ff6175 = (&DAT_00024b3c)[(short)(ushort)DAT_00ffe10f];
      if (DAT_00ffe115 < (byte)(&DAT_00024b3c)[(short)(ushort)DAT_00ffe10f]) {
        DAT_00ff6175 = DAT_00ffe115;
      }
      return;
    }
  } while( true );
}

