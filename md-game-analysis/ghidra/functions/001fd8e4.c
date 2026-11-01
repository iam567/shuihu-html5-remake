/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001fd8e4 */

undefined8 FUN_001fd8e4(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  DAT_00fff000 = DAT_00fff000 + 0x100;
  DAT_00fff008._0_2_ = DAT_00fff008._0_2_ + 0x100;
  DAT_00ff0f62 = DAT_00ff0f62 + 1;
  if (4 < DAT_00ff0f62) {
    DAT_00ff0f62 = 0;
    DAT_00fff004 = *(undefined2 *)((short)((DAT_00ff0f66 & 3) << 1) + 0xff8000);
    DAT_00fff00c._0_2_ = *(undefined2 *)((int)&DAT_00ff8008 + (int)(short)((DAT_00ff0f6a & 3) << 1))
    ;
    DAT_00ff0f66 = (DAT_00ff0f66 & 3) + 1;
    DAT_00ff0f6a = (DAT_00ff0f6a & 3) + 1;
    return CONCAT44(in_D0,in_D1);
  }
  return CONCAT44(in_D0,in_D1);
}

