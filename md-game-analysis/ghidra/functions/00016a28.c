/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00016a28 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016a28(void)

{
  short sVar1;
  undefined4 *puVar2;
  
  sVar1 = 0x35;
  puVar2 = (undefined4 *)&DAT_00ff6328;
  do {
    *puVar2 = 0;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
  } while (sVar1 != -1);
  _DAT_00ff6320 = 0;
  _DAT_00ff6324 = 0xb4;
  Seed_e50();
  DAT_00ff630c = (DAT_00ffe1f0 - DAT_00ff6014) + 0x80;
  DAT_00ff630e = (DAT_00ffe1f2 - DAT_00ff6016) + 0x80;
  DAT_00ff6328 = DAT_00ff630c;
  DAT_00ff632a = DAT_00ff630e;
  DAT_00ff632c = DAT_00ff630c;
  DAT_00ff632e = DAT_00ff630e;
  DAT_00ff6312 = 1;
  DAT_00ff6311 = 0;
  DAT_00ff6036 = 0;
  DAT_00ff6154 = 1;
  return;
}

