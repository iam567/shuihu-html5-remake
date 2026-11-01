/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001fe408 */

undefined8 FUN_001fe408(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_0001da54();
  if ((DAT_00ff0f4e & 0x10) == 0) {
    FUN_0001da54();
    if ((DAT_00ff0f4e & 0x10) == 0) {
      FUN_0001da54();
      if (((DAT_00ff0f4e & 0x10) == 0) && (DAT_00ff0a2a != '\0')) {
        return CONCAT44(in_D0,in_D1);
      }
    }
  }
  DAT_00ff0f4c = DAT_00ff0f4c | 0x20;
  return CONCAT44(in_D0,in_D1);
}

