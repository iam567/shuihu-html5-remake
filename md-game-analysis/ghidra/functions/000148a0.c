/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000148a0 */

void FUN_000148a0(void)

{
  short sVar1;
  bool bVar2;
  undefined2 *unaff_A2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  
  if (DAT_00ff6300 != '\0') {
    puVar3 = &DAT_00ff6380;
    bVar2 = false;
    sVar1 = 0xb;
    do {
      puVar4 = puVar3 + 1;
      *unaff_A2 = *puVar3;
      puVar3 = puVar3 + 2;
      unaff_A2[1] = *puVar4;
      unaff_A2[2] = 0x43;
      if (bVar2) {
        unaff_A2[2] = 0x44;
      }
      bVar2 = (bool)(bVar2 ^ 1);
      DAT_00ff6012 = DAT_00ff6012 + 1;
      unaff_A2 = unaff_A2 + 3;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
  }
  return;
}

