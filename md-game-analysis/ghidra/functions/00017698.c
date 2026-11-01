/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00017698 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Seed_17698(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar2 = &DAT_000176ea;
  puVar4 = (undefined4 *)&DAT_00ffe630;
  sVar1 = 0x13;
  do {
    *puVar4 = *puVar2;
    puVar4[1] = puVar2[1];
    puVar3 = puVar2 + 3;
    puVar5 = puVar4 + 3;
    puVar4[2] = puVar2[2];
    puVar2 = puVar2 + 4;
    puVar4 = puVar4 + 4;
    *puVar5 = *puVar3;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  _DAT_00ffe610 = 0x1000000;
  DAT_00ffe614 = 0;
  DAT_00ffe618 = 0;
  DAT_00ffe61c = 0;
  DAT_00ffe620 = 0;
  DAT_00ffe115 = 1;
  return;
}

