/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000170ae */

void FUN_000170ae(void)

{
  if ((DAT_00ff603d & 1) == 0) {
    DAT_00ff603d = DAT_00ff603d | 3;
    DAT_00ff6130 = &PTR_DAT_000170d8;
  }
  return;
}

