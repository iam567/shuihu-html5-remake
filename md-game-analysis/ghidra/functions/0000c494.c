/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000c494 */

void FUN_0000c494(void)

{
  int iVar1;
  short sVar2;
  
  if ((((DAT_00ff6104 != '\0') && (DAT_00ff6039 == '\0')) && (DAT_00ff604c == '\0')) &&
     ((DAT_00ff606a == '\0' && (DAT_00ff606e == '\0')))) {
    if (DAT_00ff6106 == '\0') {
      FUN_0000c74c();
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
        DAT_00ff6098 = *(short *)((int)&DAT_00ffe792 + iVar1);
        DAT_00ff60a0 = 0;
        DAT_00ff60a2 = 0x1c;
        DAT_00ff60a4 = 0xd;
        DAT_00ff60a6 = 0x10;
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
        if (DAT_00ff6098 == 0) {
          (&DAT_00ffe79d)[(short)((ushort)DAT_00ff606b << 6)] = 0xff;
          FUN_00009df8();
          DAT_00ff601c = 8;
          DAT_00ff6019 = DAT_00ff6019 | 4;
          DAT_00ff601b = 7;
          DAT_00ff601a = 0;
          DAT_00ff6106 = '\x04';
        }
        else {
          DAT_00ff6106 = '\0';
          DAT_00ff606b = DAT_00ff606b + 1;
        }
      }
      else {
        DAT_00ff609a = DAT_00ff609a + -1;
      }
    }
    else if (DAT_00ff6106 == '\x04') {
      if ((DAT_00ff6019 & 4) == 0) {
        sVar2 = (ushort)DAT_00ff606b << 6;
        *(undefined1 *)((int)&DAT_00ffe780 + (int)sVar2) = 0;
        DAT_00ff630c = (*(short *)((int)&DAT_00ffe780 + sVar2 + 2) - DAT_00ff6014) + 0x80;
        DAT_00ff630e = (*(short *)((int)&DAT_00ffe784 + (int)sVar2) - DAT_00ff6016) + 0x80;
        FUN_00016950();
        DAT_00ff6301 = 0;
        Seed_e50();
        DAT_00ff6310 = '\x01';
        DAT_00ff6300 = DAT_00ff6300 | 1;
        DAT_00ff6106 = '\x05';
      }
    }
    else if ((DAT_00ff6106 == '\x05') && (DAT_00ff6310 == '\0')) {
      DAT_00ff6106 = '\0';
      DAT_00ff606b = DAT_00ff606b + 1;
    }
  }
  return;
}

