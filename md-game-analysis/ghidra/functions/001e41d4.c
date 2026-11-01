/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e41d4 */

undefined8 FUN_001e41d4(void)

{
  byte bVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  
  Ram00a11100 = 0x100;
  do {
    bVar1 = DAT_00a11100;
  } while ((bVar1 & 1) != 0);
  if (DAT_00ff6d00 < 0) {
    FUN_001e7642();
  }
  else {
    FUN_001e42bc();
  }
  Ram00a11100 = 0;
  return CONCAT44(in_D0,in_D1);
}

