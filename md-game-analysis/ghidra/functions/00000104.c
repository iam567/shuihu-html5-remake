/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00000104 */

undefined8 Vector_78(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_001e4100();
  DAT_00ffe120 = DAT_00ffe120 + 1;
  if (DAT_00ff6000 == '\0') {
    DAT_00ff6000 = -1;
    DAT_00ff6010 = DAT_00ff6010 + 1;
    Ram00c00004 = 0x8134;
    FUN_00000478();
    FUN_0000032c();
    FUN_0000036e();
    FUN_0000018a();
    FUN_00027a3e();
    if (DAT_00ffe116 == '\0') {
      FUN_00001298();
    }
    else if (DAT_00ffe116 == '\x01') {
      FUN_00002768();
    }
    Ram00c00004 = 0x8174;
  }
  return CONCAT44(in_D0,in_D1);
}

