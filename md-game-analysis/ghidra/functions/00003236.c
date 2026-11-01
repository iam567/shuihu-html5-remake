/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003236 */

void FUN_00003236(void)

{
  byte bVar1;
  
  FUN_00003218();
  bVar1 = DAT_00ffe006 & 3;
  if (bVar1 == 0) {
    DAT_00ff6026 = DAT_00ff6026 + -1;
  }
  else if (bVar1 == 1) {
    DAT_00ff6026 = DAT_00ff6026 + 1;
  }
  else if (bVar1 == 2) {
    DAT_00ff6024 = DAT_00ff6024 + -1;
  }
  else {
    DAT_00ff6024 = DAT_00ff6024 + 1;
  }
  return;
}

