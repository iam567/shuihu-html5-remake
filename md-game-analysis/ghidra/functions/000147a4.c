/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000147a4 */

void FUN_000147a4(void)

{
  uint uVar1;
  ushort uVar2;
  
  uVar2 = 0x531;
  for (uVar1 = (uint)DAT_00ff6142; (short)uVar1 != 0; uVar1 = uVar1 / 10) {
    FUN_00002846();
    uVar2 = uVar2 - 2;
  }
  if (0x52b < uVar2) {
    FUN_00014800();
  }
  return;
}

