/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000ffc2 */

/* WARNING: This function may have set the stack pointer */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0000ffc2(void)

{
  short sVar1;
  ushort uVar2;
  char cVar3;
  undefined4 *puVar4;
  undefined4 unaff_A3;
  
  DAT_00ff6120 = 0;
  DAT_00ff6130 = unaff_A3;
  FUN_00003ae4();
  puVar4 = &DAT_00ffe780;
  sVar1 = 0x1d;
  do {
    *(undefined1 *)((int)puVar4 + 1) = 4;
    puVar4 = puVar4 + 0x10;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00ff611d = '\x01';
  while (DAT_00ff611d != '\0') {
    FUN_00000e40();
    FUN_0000ec60();
    FUN_00003a82();
  }
  _DAT_00ffe104 = DAT_00ffe1f8;
  uVar2 = (ushort)(byte)(DAT_00ffe1f4 - 1);
  puVar4 = &DAT_00ffe780;
  do {
    cVar3 = *(char *)((int)puVar4 + 7);
    if (cVar3 == '\x15') {
      cVar3 = '\x01';
    }
    sVar1 = (ushort)(byte)(cVar3 - 1) << 4;
    *(undefined2 *)((int)&DAT_00ffe636 + (int)sVar1) = *(undefined2 *)(puVar4 + 4);
    (&DAT_00ffe638)[sVar1] = *(undefined1 *)(puVar4 + 9);
    puVar4 = puVar4 + 0x10;
    uVar2 = uVar2 - 1;
  } while (uVar2 != 0xffff);
  DAT_00ff6d00 = 9;
  FUN_001e41d4();
  FUN_000248e2();
  FUN_000184f4();
  FUN_00024f06();
  FUN_00027ebe();
  DAT_00ff603d = 0;
  DAT_00ff6036 = 0;
  Seed_7a6();
  return;
}

