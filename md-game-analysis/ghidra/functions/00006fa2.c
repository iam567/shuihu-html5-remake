/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006fa2 */

undefined8 FUN_00006fa2(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  undefined2 unaff_D6w;
  
  Ram00c00004 = (uint)(ushort)((short)in_D0 * 2 + (short)in_D1 * 0x80) * 0x10000 + 0x40000003;
  Ram00c00000 = unaff_D6w;
  return CONCAT44(in_D0,in_D1);
}

