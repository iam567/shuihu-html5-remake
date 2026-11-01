/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d962 */

void FUN_0000d962(void)

{
  int iVar1;
  
  if ((((DAT_00ff611c != '\0') && (DAT_00ff6039 == '\0')) && (DAT_00ff604c == '\0')) &&
     ((DAT_00ff606a == '\0' && (DAT_00ff606e == '\0')))) {
    if (DAT_00ff6106 == '\0') {
      FUN_0000db02();
    }
    else if (DAT_00ff6106 == '\x01') {
      if (DAT_00ff605a == '\0') {
        DAT_00ff60c8 = 5;
        FUN_0000ca16();
        DAT_00ff6107 = '<';
        DAT_00ff6106 = '\x02';
      }
    }
    else if (DAT_00ff6106 == '\x02') {
      if (DAT_00ff6107 == '\0') {
        iVar1 = (int)(short)((ushort)DAT_00ff606b << 6);
        (&DAT_00ffe79d)[iVar1] = 4;
        DAT_00ff6094 = *(undefined2 *)((int)&DAT_00ffe792 + iVar1);
        DAT_00ff6096 = *(undefined2 *)((int)&DAT_00ffe79e + iVar1);
        DAT_00ff609a = '`';
        DAT_00ff609d = 1;
        DAT_00ff6142 = *(ushort *)((int)&DAT_00ffe79e + iVar1) / 6;
        DAT_00ff6148 = 1;
        DAT_00ff6144 = *(undefined2 *)((int)&DAT_00ffe780 + iVar1 + 2);
        DAT_00ff6146 = *(undefined2 *)((int)&DAT_00ffe784 + iVar1);
        *(short *)((int)&DAT_00ffe792 + iVar1) =
             *(short *)((int)&DAT_00ffe792 + iVar1) - DAT_00ff6142;
        if (*(short *)((int)&DAT_00ffe792 + iVar1) < 1) {
          *(undefined2 *)((int)&DAT_00ffe792 + iVar1) = 1;
        }
        DAT_00ff6098 = *(undefined2 *)((int)&DAT_00ffe792 + iVar1);
        DAT_00ff60a4 = 0xd;
        DAT_00ff60a6 = 0x10;
        DAT_00ff60a0 = 0;
        DAT_00ff60a2 = 0x1c;
        Seed_e50();
        FUN_00009c4a();
        DAT_00ff6106 = '\x03';
      }
      else {
        DAT_00ff6107 = DAT_00ff6107 + -1;
        if (DAT_00ff6107 == '\0') {
          FUN_00001098();
        }
      }
    }
    else if (DAT_00ff6106 == '\x03') {
      if (DAT_00ff609a == '\0') {
        FUN_00001098();
        DAT_00ff6106 = '\0';
        DAT_00ff606b = DAT_00ff606b + 1;
      }
      else {
        DAT_00ff609a = DAT_00ff609a + -1;
      }
    }
  }
  return;
}

