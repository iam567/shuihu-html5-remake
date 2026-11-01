/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00018aaa */

void FUN_00018aaa(void)

{
  uint uVar1;
  short sVar3;
  uint uVar2;
  byte *pbVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  
  sVar3 = 0x13f;
  puVar5 = (undefined4 *)&DAT_00ff8000;
  do {
    *puVar5 = 0;
    uVar1 = DAT_00ff616c;
    sVar3 = sVar3 + -1;
    puVar5 = puVar5 + 1;
  } while (sVar3 != -1);
  puVar6 = &DAT_00ff8000;
  uVar2 = 0;
  pbVar4 = &DAT_00ffe610;
  puVar5 = &DAT_00018b3c;
  while( true ) {
    if (*pbVar4 == 0) break;
    sVar3 = (*pbVar4 - 1) * 0x10;
    *puVar6 = (&DAT_00ffe630)[sVar3];
    puVar6[7] = (&DAT_00ffe631)[sVar3];
    *(undefined4 *)(puVar6 + 8) = *(undefined4 *)((int)&DAT_00ffe632 + (int)sVar3);
    *(undefined2 *)(puVar6 + 0x10) = *(undefined2 *)((int)&DAT_00ffe636 + (int)sVar3);
    puVar6[0x24] = (&DAT_00ffe638)[sVar3];
    puVar6[0x2a] = (&DAT_00ffe639)[sVar3];
    *(undefined4 *)(puVar6 + 0x26) = *(undefined4 *)((int)&DAT_00ffe63a + (int)sVar3);
    puVar6[0x21] = (&DAT_00ffe63e)[sVar3];
    *(undefined4 *)(puVar6 + 2) = *puVar5;
    puVar6[1] = 4;
    puVar6[0x1d] = 1;
    if ((uVar1 & 1 << (uVar2 & 0x1f)) != 0) {
      puVar6[0x1d] = 0;
    }
    uVar2 = (uint)(byte)((char)uVar2 + 1);
    puVar6 = puVar6 + 0x40;
    pbVar4 = pbVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  return;
}

