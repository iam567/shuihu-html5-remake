/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e4100 */

undefined8 FUN_001e4100(void)

{
  byte bVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  
  Ram00a11100 = 0x100;
  do {
    bVar1 = DAT_00a11100;
  } while ((bVar1 & 1) != 0);
  FUN_001e4150();
  FUN_001e4be8();
  FUN_001e76a6();
  DAT_00a04000 = 0x2a;
  Ram00a11100 = 0;
  return CONCAT44(in_D0,in_D1);
}

