/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000043ca */

void FUN_000043ca(void)

{
  int iVar1;
  short sVar2;
  ushort uVar3;
  
  if (((((DAT_00ffe1f7 == '\0') && (DAT_00ff6036 != '\0')) && (DAT_00ff6039 == '\0')) &&
      ((DAT_00ff604c == '\0' && (DAT_00ff606a == '\0')))) &&
     ((DAT_00ff6104 == '\0' && ((DAT_00ff6105 == '\0' && (DAT_00ff6159 == '\0')))))) {
    DAT_00ff6048 = (DAT_00ffe1f0 - DAT_00ff6014) + 0x80;
    DAT_00ff604a = (DAT_00ffe1f2 - DAT_00ff6016) + 0x80;
    if (DAT_00ff6085 == '\0') {
      FUN_00004e26();
      return;
    }
    if (DAT_00ff6085 == '\x01') {
      FUN_0000bfde();
      DAT_00ff6085 = 3;
      return;
    }
    if (DAT_00ff6085 == '\x02') {
      FUN_00005162();
      return;
    }
    if (DAT_00ff6085 == '\x03') {
      FUN_00004b8a();
      return;
    }
    if (DAT_00ff6085 == '\x04') {
      FUN_00005644();
      return;
    }
    if (DAT_00ff6085 == '\x05') {
      FUN_00004976();
      return;
    }
    if (DAT_00ff6085 == '\x06') {
      FUN_00004b40();
      return;
    }
    if (DAT_00ff6085 == '\a') {
      FUN_0000aafe();
      return;
    }
    if (DAT_00ff6085 == '\b') {
      FUN_0000b3c4();
      return;
    }
    if (DAT_00ff6085 == '\t') {
      FUN_0000b4a8();
      return;
    }
    if (DAT_00ff6085 == '\n') {
      FUN_0000487e();
      return;
    }
    if (DAT_00ff6085 == '\v') {
      FUN_0000baec();
      return;
    }
    if (DAT_00ff6085 == '\f') {
      if ((DAT_00ff6019 & 4) == 0) {
        FUN_00027f68();
        sVar2 = (ushort)DAT_00ff609f << 6;
        *(undefined1 *)((int)&DAT_00ffe780 + (int)sVar2) = 0;
        if ((&DAT_00ffe7aa)[sVar2] == '{') {
          DAT_00ff6156 = (&DAT_00ffe794)[sVar2];
          FUN_000170ae();
        }
        else {
          DAT_00ff630c = (*(short *)((int)&DAT_00ffe780 + sVar2 + 2) - DAT_00ff6014) + 0x80;
          DAT_00ff630e = (*(short *)((int)&DAT_00ffe784 + (int)sVar2) - DAT_00ff6016) + 0x80;
          FUN_00016950();
          DAT_00ff6301 = 0;
          Seed_e50();
          DAT_00ff6310 = '\x01';
          DAT_00ff6300 = DAT_00ff6300 | 1;
        }
        DAT_00ff6085 = '\r';
      }
    }
    else if ((DAT_00ff6085 == '\r') && (DAT_00ff6310 == '\0')) {
      if ((&DAT_00ffe7aa)[(short)((ushort)DAT_00ff606b << 6)] == 'z') {
        DAT_00ffe1e0 = DAT_00ffe1e0 | 1 << (DAT_00ff606b & 0x1f);
        DAT_00ff6085 = '\x14';
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
        DAT_00ff6085 = '\0';
      }
    }
    else if (DAT_00ff6085 == '\x0e') {
      if ((DAT_00ff6019 & 4) == 0) {
        FUN_00027f68();
        sVar2 = (ushort)DAT_00ff606b << 6;
        *(undefined1 *)((int)&DAT_00ffe780 + (int)sVar2) = 0;
        if ((&DAT_00ffe7aa)[sVar2] == '{') {
          DAT_00ff6156 = (&DAT_00ffe794)[sVar2];
          FUN_000170ae();
        }
        else {
          DAT_00ff630c = (*(short *)((int)&DAT_00ffe780 + sVar2 + 2) - DAT_00ff6014) + 0x80;
          DAT_00ff630e = (*(short *)((int)&DAT_00ffe784 + (int)sVar2) - DAT_00ff6016) + 0x80;
          FUN_00016950();
          DAT_00ff6301 = 0;
          Seed_e50();
          DAT_00ff6310 = '\x01';
          DAT_00ff6300 = DAT_00ff6300 | 1;
        }
        DAT_00ff6085 = '\r';
      }
    }
    else if (DAT_00ff6085 == '\x0f') {
      if (DAT_00ff6107 == '\0') {
        DAT_00ff60aa = 0;
        FUN_00001098();
        DAT_00ff6085 = '\0';
        DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
        uVar3 = (ushort)DAT_00ff606b;
        *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar3 << 6) + 1) = 0x10;
        *(undefined1 *)((int)&DAT_00ffe784 + (short)(uVar3 << 6) + 2) = 1;
      }
      else {
        DAT_00ff6107 = DAT_00ff6107 + -1;
      }
    }
    else {
      if (DAT_00ff6085 == '\x10') {
        FUN_000154f0();
        return;
      }
      if (DAT_00ff6085 == '\x11') {
        FUN_00027f48();
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6152 = 100;
        FUN_00015462();
        DAT_00ff6151 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00006912();
        FUN_00006928();
        FUN_00001098();
        DAT_00ff6120 = 0;
        Ram00c00004 = 0x74000003;
        Ram00c00000 = DAT_00ff6008 + -4;
        return;
      }
      if (DAT_00ff6085 == '\x12') {
        FUN_00015616();
        return;
      }
      if (DAT_00ff6085 == '\x13') {
        FUN_00015aee();
        return;
      }
      if (DAT_00ff6085 == '\x14') {
        FUN_00016c68();
        return;
      }
    }
  }
  return;
}

