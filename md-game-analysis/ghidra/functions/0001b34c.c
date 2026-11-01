/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001b34c */

void FUN_0001b34c(void)

{
  short sVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  undefined1 *puVar4;
  
  sVar1 = 0x13f;
  puVar3 = (undefined4 *)&DAT_00ff8000;
  do {
    *puVar3 = 0;
    sVar1 = sVar1 + -1;
    puVar3 = puVar3 + 1;
  } while (sVar1 != -1);
  puVar4 = &DAT_00ff8000;
  pbVar2 = &DAT_00ffe610;
  puVar3 = &DAT_0001b3c8;
  while( true ) {
    if (*pbVar2 == 0) break;
    sVar1 = (*pbVar2 - 1) * 0x10;
    *puVar4 = (&DAT_00ffe630)[sVar1];
    puVar4[7] = (&DAT_00ffe631)[sVar1];
    *(undefined4 *)(puVar4 + 8) = *(undefined4 *)((int)&DAT_00ffe632 + (int)sVar1);
    *(undefined2 *)(puVar4 + 0x10) = *(undefined2 *)((int)&DAT_00ffe636 + (int)sVar1);
    puVar4[0x24] = (&DAT_00ffe638)[sVar1];
    puVar4[0x2a] = (&DAT_00ffe639)[sVar1];
    *(undefined4 *)(puVar4 + 0x26) = *(undefined4 *)((int)&DAT_00ffe63a + (int)sVar1);
    puVar4[0x21] = (&DAT_00ffe63e)[sVar1];
    *(undefined4 *)(puVar4 + 2) = *puVar3;
    puVar4[1] = 4;
    puVar4[0x1d] = 1;
    puVar4 = puVar4 + 0x40;
    pbVar2 = pbVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return;
}

