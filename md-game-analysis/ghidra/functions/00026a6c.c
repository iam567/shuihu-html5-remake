/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00026a6c */

void FUN_00026a6c(void)

{
  uint uVar1;
  char in_D0b;
  uint uVar2;
  undefined1 *puVar3;
  
  puVar3 = &DAT_00200251;
  if ((in_D0b != '\0') && (puVar3 = &DAT_00202251, in_D0b != '\x01')) {
    puVar3 = &DAT_00203251;
  }
  uVar2 = CONCAT31(CONCAT21(CONCAT11(*puVar3,puVar3[2]),puVar3[4]),puVar3[6]);
  uVar1 = uVar2 / 0xe10 & 0xffff;
  DAT_00ff6110 = (short)((uVar2 % 0xe10) / 0x3c);
  DAT_00ff6112 = (short)(uVar1 / 0x3c);
  DAT_00ff6114 = (short)(uVar1 % 0x3c);
  return;
}

