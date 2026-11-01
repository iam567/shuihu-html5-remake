/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001fa0d0 */

undefined8 FUN_001fa0d0(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_00006560(&DAT_00ffa000,&DAT_000533c4 + (ushort)(DAT_000533d6 + 0x1a));
  DAT_00ff02b0 = &DAT_00ffa000;
  DAT_00ff02b4 = &DAT_00038238;
  DAT_00ff1365 = DAT_00ff1365 + '\x01';
  DAT_00ff1362 = DAT_00ff1362 + '\x01';
  return CONCAT44(in_D0,in_D1);
}

