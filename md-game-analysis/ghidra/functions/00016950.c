/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00016950 */

void FUN_00016950(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  sVar1 = 0x17;
  puVar2 = &DAT_00016968;
  puVar3 = (undefined4 *)&DAT_00ff6320;
  do {
    *puVar3 = *puVar2;
    sVar1 = sVar1 + -1;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  } while (sVar1 != -1);
  return;
}

