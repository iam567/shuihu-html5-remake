/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00018274 */

void Seed_18274(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  sVar1 = 0xf;
  puVar2 = &DAT_00ffe2c0;
  puVar3 = &DAT_0001828c;
  do {
    *puVar2 = *puVar3;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  } while (sVar1 != -1);
  return;
}

