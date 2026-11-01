/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001fd066 */

undefined8 FUN_001fd066(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  if ((DAT_00ff052a < '\x01') && (DAT_00ff056a < '\x02')) {
    DAT_00ff0f4c = DAT_00ff0f4c | 0x40;
    FUN_0001d3da();
    return CONCAT44(in_D0,in_D1);
  }
  return CONCAT44(in_D0,in_D1);
}

