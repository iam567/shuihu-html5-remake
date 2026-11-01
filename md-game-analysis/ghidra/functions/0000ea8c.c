/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000ea8c */

void FUN_0000ea8c(void)

{
  ushort uVar1;
  char unaff_D7b;
  
  DAT_00ff609a = DAT_00ff609a + -1;
  if (DAT_00ff609a == '\0') {
    if (DAT_00ff6092 == 0) {
      (&DAT_00ffe79d)[(short)((ushort)DAT_00ff609f << 6)] = 0xff;
      FUN_00009df8();
      DAT_00ff601c = 8;
      DAT_00ff6019 = DAT_00ff6019 | 4;
      DAT_00ff601b = 7;
      DAT_00ff601a = 0;
      FUN_00001098();
      DAT_00ff6085 = 6;
    }
    else if (DAT_00ff60b2 == '\0') {
      FUN_00001098();
      FUN_00008bb4();
      if (unaff_D7b == '\0') {
        DAT_00ff6085 = 0;
        DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
        uVar1 = (ushort)DAT_00ff606b;
        *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar1 << 6) + 1) = 0x10;
        *(undefined1 *)((int)&DAT_00ffe784 + (short)(uVar1 << 6) + 2) = 1;
      }
      else {
        FUN_00007c14();
        DAT_00ff6085 = 9;
      }
    }
    else {
      DAT_00ff60b2 = '\0';
      FUN_0000e966();
      DAT_00ff6085 = 5;
    }
  }
  return;
}

