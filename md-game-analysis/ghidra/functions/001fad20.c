/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001fad20 */

undefined8 FUN_001fad20(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_0001da54();
  if ((DAT_00ff0f4e & 0x10) != 0) {
    FUN_0001d3da();
    FUN_000faebe();
    return CONCAT44(in_D0,in_D1);
  }
  return CONCAT44(in_D0,in_D1);
}

