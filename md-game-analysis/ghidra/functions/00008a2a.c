/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00008a2a */

void FUN_00008a2a(void)

{
  ushort uVar1;
  
  DAT_00ff609a = DAT_00ff609a + -1;
  if (DAT_00ff609a == '\0') {
    FUN_00001098();
    DAT_00ff6085 = 0;
    if (DAT_00ff6092 == 0) {
      (&DAT_00ffe79d)[(short)((ushort)DAT_00ff606b << 6)] = 0xff;
      FUN_00009df8();
      DAT_00ff601c = 8;
      DAT_00ff6019 = DAT_00ff6019 | 4;
      DAT_00ff601b = 7;
      DAT_00ff601a = 0;
      DAT_00ff6085 = 0xb;
    }
    else {
      DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
      uVar1 = (ushort)DAT_00ff606b;
      *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar1 << 6) + 1) = 0x11;
      *(undefined1 *)((int)&DAT_00ffe784 + (short)(uVar1 << 6) + 2) = 1;
    }
  }
  return;
}

