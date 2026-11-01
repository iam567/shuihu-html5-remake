/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000353c */

undefined8 FUN_0000353c(void)

{
  int iVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  
  iVar1 = (uint)(ushort)((short)in_D0 * 2 + (short)in_D1 * 0x80) * 0x10000;
  Ram00c00004 = iVar1 + 0x40000003;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00004 = iVar1 + 0x40800003;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00004 = iVar1 + 0x41000003;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00004 = iVar1 + 0x41800003;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  Ram00c00000 = 0;
  return CONCAT44(in_D0,in_D1);
}

