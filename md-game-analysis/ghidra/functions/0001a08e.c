/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001a08e */

void FUN_0001a08e(void)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  byte bVar5;
  byte bVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  
  bVar5 = 0;
  bVar6 = 0x6f;
  if (DAT_00ff6177 != '\0') {
    bVar5 = 0x6f;
    bVar6 = 0x7f;
    if (DAT_00ff6177 != '\x02') {
      bVar5 = 0x7f;
      bVar6 = 0x8f;
    }
  }
  cVar1 = (&DAT_00ffe638)
          [(short)((ushort)(byte)((&DAT_00ffe610)[(short)(ushort)DAT_00ff615b] - 1) << 4)];
  DAT_00ff6180 = '\0';
  sVar4 = 0;
  sVar3 = 0x7f;
  puVar7 = &DAT_00ff9000;
  do {
    bVar2 = (&DAT_00ffe400)[sVar4];
    puVar8 = puVar7;
    if (((bVar5 < bVar2) && (bVar2 <= bVar6)) &&
       ((*(uint *)(&DAT_0001a130 + (short)((ushort)bVar2 << 2)) & 1 << ((byte)(cVar1 - 1) & 0x1f))
        != 0)) {
      DAT_00ff6180 = DAT_00ff6180 + '\x01';
      puVar8 = puVar7 + 1;
      *puVar7 = (char)sVar4;
    }
    sVar4 = sVar4 + 1;
    sVar3 = sVar3 + -1;
    puVar7 = puVar8;
  } while (sVar3 != -1);
  return;
}

