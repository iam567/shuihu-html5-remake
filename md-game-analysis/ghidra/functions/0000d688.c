/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d688 */

void FUN_0000d688(void)

{
  char cVar1;
  
  DAT_00ff60e8 = (int)&DAT_00ffe780 + (int)(short)((ushort)DAT_00ff610b << 6);
  (&DAT_00ffe79d)[(short)((ushort)DAT_00ff610b << 6)] = 0x60;
  FUN_00009c4a();
  DAT_00ff60aa = 0xff;
  DAT_00ff60ab = 7;
  DAT_00ff6107 = 0x60;
  DAT_00ff6109 = DAT_00ff610c + '\x02';
  DAT_00ff610a = 0x60;
  FUN_00027f48();
  cVar1 = FUN_0000d712();
  if (cVar1 == '\0') {
    DAT_00ff6109 = DAT_00ff6109 + '\x04';
  }
  else {
    *(undefined1 *)(DAT_00ff60e8 + (short)(ushort)(byte)(DAT_00ff610c + 9)) = 3;
  }
  return;
}

