/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00004976 */

void FUN_00004976(void)

{
  int iVar1;
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
      DAT_00ff6085 = 0xc;
    }
    else if (DAT_00ff60b2 == '\0') {
      FUN_00001098();
      FUN_00004ab4();
      if (unaff_D7b == '\0') {
        if ((&DAT_00ffe7aa)[(short)((ushort)DAT_00ff606b << 6)] == 'z') {
          DAT_00ffe1e0 = DAT_00ffe1e0 | 1 << (DAT_00ff606b & 0x1f);
          DAT_00ff6085 = 0x14;
          FUN_00006912();
          FUN_00006928();
          FUN_00001098();
          FUN_00006f0e();
          FUN_00006986();
          FUN_00006c86();
          FUN_00007c14();
        }
        else {
          DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
          iVar1 = (int)(short)((ushort)DAT_00ff606b << 6);
          *(undefined1 *)((int)&DAT_00ffe780 + iVar1 + 1) = 0x10;
          *(undefined1 *)((int)&DAT_00ffe784 + iVar1 + 2) = 1;
          DAT_00ff6085 = 0;
        }
      }
      else {
        FUN_00007c14();
        DAT_00ff6085 = 9;
      }
    }
    else {
      DAT_00ff60b2 = '\0';
      FUN_00005ce6();
      DAT_00ff6085 = 5;
    }
  }
  return;
}

