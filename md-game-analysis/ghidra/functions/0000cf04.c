/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000cf04 */

void FUN_0000cf04(void)

{
  (&DAT_00ffe79d)[(short)((ushort)DAT_00ff6108 << 6)] = 0x60;
  FUN_0000cf52();
  DAT_00ff610a = 0x60;
  FUN_00009c4a();
  DAT_00ff60aa = 0xff;
  DAT_00ff60ab = 7;
  DAT_00ff6107 = 0x60;
  FUN_00027f48();
  return;
}

