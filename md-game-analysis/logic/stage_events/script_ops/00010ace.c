/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00010ace */

void FUN_00010ace(void)

{
  short sVar1;
  char cVar3;
  short sVar2;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 unaff_A3;
  
  puVar4 = (undefined4 *)&DAT_00ffe000;
  sVar1 = 0xf;
  DAT_00ff6130 = unaff_A3;
  do {
    *puVar4 = 0;
    puVar4[1] = 0;
    puVar5 = puVar4 + 3;
    puVar4[2] = 0;
    puVar4 = puVar4 + 4;
    *puVar5 = 0;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00ffe116 = 0;
  DAT_00ffe1f6 = 2;
  puVar4 = &DAT_00ffe780;
  sVar1 = DAT_00ffe1f4 - 1;
  do {
    cVar3 = *(char *)((int)puVar4 + 7);
    if (cVar3 == '\x15') {
      cVar3 = '\x01';
    }
    sVar2 = (ushort)(byte)(cVar3 - 1) << 4;
    *(undefined4 *)((int)&DAT_00ffe632 + (int)sVar2) = puVar4[2];
    *(undefined2 *)((int)&DAT_00ffe636 + (int)sVar2) = *(undefined2 *)(puVar4 + 4);
    (&DAT_00ffe638)[sVar2] = *(undefined1 *)(puVar4 + 9);
    puVar4 = puVar4 + 0x10;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}

