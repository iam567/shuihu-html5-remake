/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00005644 */

void FUN_00005644(void)

{
  int iVar1;
  char cVar2;
  ushort uVar3;
  byte bVar4;
  
  if (DAT_00ff7180 != 0xff) {
    if ((DAT_00ff6004 & 0x40) != 0) {
      FUN_00001098();
      DAT_00ffe1e0 = DAT_00ffe1e0 & ~(1 << (DAT_00ff606b & 0x1f));
      DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
      iVar1 = (int)(short)((ushort)DAT_00ff606b << 6);
      *(undefined1 *)((int)&DAT_00ffe780 + iVar1 + 1) = 4;
      *(undefined1 *)((int)&DAT_00ffe784 + iVar1 + 2) = 1;
      (&DAT_00ffe7ab)[(short)(ushort)DAT_00ff60b7 + iVar1] =
           (&DAT_00ffe7ab)[(short)(ushort)DAT_00ff60b7 + iVar1] + -1;
      DAT_00ff609f = (&DAT_00ff7180)[(short)(ushort)DAT_00ff6087];
      if (DAT_00ff60bb < 2) {
        FUN_00009c4a();
        FUN_00005cc6();
        FUN_00005ce6();
        DAT_00ff6085 = 5;
      }
      else if (DAT_00ff60bb == 2) {
        FUN_0000a5fe();
        DAT_00ff6085 = 6;
      }
      else if (DAT_00ff60bb == 3) {
        DAT_00ff60e8 = (int)&DAT_00ffe780 + (int)(short)((ushort)DAT_00ff609f << 6);
        (&DAT_00ffe79d)[(short)((ushort)DAT_00ff609f << 6)] = 0x60;
        cVar2 = FUN_00005fdc();
        if (cVar2 == '\0') {
          DAT_00ff6109 = 9;
        }
        else {
          *(undefined1 *)(DAT_00ff60e8 + 0xc) = 3;
          DAT_00ff6109 = 5;
          FUN_00014ff2();
        }
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == 4) {
        DAT_00ff60e8 = (int)&DAT_00ffe780 + (int)(short)((ushort)DAT_00ff609f << 6);
        (&DAT_00ffe79d)[(short)((ushort)DAT_00ff609f << 6)] = 0x60;
        cVar2 = FUN_00005fdc();
        if (cVar2 == '\0') {
          DAT_00ff6109 = 10;
        }
        else {
          *(undefined1 *)(DAT_00ff60e8 + 0xd) = 3;
          DAT_00ff6109 = 6;
          FUN_00014ff2();
        }
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == 5) {
        DAT_00ff60e8 = (int)&DAT_00ffe780 + (int)(short)((ushort)DAT_00ff609f << 6);
        (&DAT_00ffe79d)[(short)((ushort)DAT_00ff609f << 6)] = 0x60;
        cVar2 = FUN_00005fdc();
        if (cVar2 == '\0') {
          DAT_00ff6109 = 0xb;
        }
        else {
          *(undefined1 *)(DAT_00ff60e8 + 0xe) = 3;
          DAT_00ff6109 = 7;
          FUN_00014ff2();
        }
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == 6) {
        DAT_00ff60e8 = (int)&DAT_00ffe780 + (int)(short)((ushort)DAT_00ff609f << 6);
        (&DAT_00ffe79d)[(short)((ushort)DAT_00ff609f << 6)] = 0x60;
        cVar2 = FUN_00005fdc();
        if (cVar2 == '\0') {
          DAT_00ff6109 = 0xc;
        }
        else {
          *(undefined1 *)(DAT_00ff60e8 + 0xf) = 3;
          DAT_00ff6109 = 8;
          FUN_00014ff2();
        }
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == 7) {
        uVar3 = (ushort)DAT_00ff609f;
        (&DAT_00ffe79d)[(short)(uVar3 << 6)] = 0x60;
        *(undefined1 *)((int)&DAT_00ffe78c + (int)(short)(uVar3 << 6)) = 0;
        FUN_00014ff2();
        DAT_00ff6109 = 1;
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == 8) {
        uVar3 = (ushort)DAT_00ff609f;
        (&DAT_00ffe79d)[(short)(uVar3 << 6)] = 0x60;
        *(undefined1 *)((int)&DAT_00ffe78c + (short)(uVar3 << 6) + 1) = 0;
        FUN_00014ff2();
        DAT_00ff6109 = 2;
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == 9) {
        uVar3 = (ushort)DAT_00ff609f;
        (&DAT_00ffe79d)[(short)(uVar3 << 6)] = 0x60;
        *(undefined1 *)((int)&DAT_00ffe78c + (short)(uVar3 << 6) + 2) = 0;
        FUN_00014ff2();
        DAT_00ff6109 = 3;
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == 10) {
        uVar3 = (ushort)DAT_00ff609f;
        (&DAT_00ffe79d)[(short)(uVar3 << 6)] = 0x60;
        *(undefined1 *)((int)&DAT_00ffe78c + (short)(uVar3 << 6) + 3) = 0;
        FUN_00014ff2();
        DAT_00ff6109 = 4;
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == 0xb) {
        uVar3 = (ushort)DAT_00ff609f;
        (&DAT_00ffe79d)[(short)(uVar3 << 6)] = 0x60;
        *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar3 << 6) + 1) = 4;
        DAT_00ffe1e0 = DAT_00ffe1e0 | 1 << (DAT_00ff609f & 0x1f);
        FUN_00014ff2();
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == 0xd) {
        uVar3 = (ushort)DAT_00ff609f;
        (&DAT_00ffe79d)[(short)(uVar3 << 6)] = 0x60;
        *(undefined4 *)((int)&DAT_00ffe78c + (int)(short)(uVar3 << 6)) = 0;
        FUN_00014ff2();
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      FUN_00006912();
      FUN_00006928();
      return;
    }
    if ((DAT_00ff6004 & 0xf) != 0) {
      FUN_00027f08();
      DAT_00ff6087 = DAT_00ff6087 + 1;
      bVar4 = (&DAT_00ff7180)[(short)(ushort)DAT_00ff6087];
      if ((&DAT_00ff7180)[(short)(ushort)DAT_00ff6087] == 0xff) {
        DAT_00ff6087 = 0;
        bVar4 = DAT_00ff7180;
      }
      DAT_00ff6036 = 0;
      DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)bVar4 << 6) + 2) >> 5;
      DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)bVar4 << 6)) >> 5;
      DAT_00ff605a = 1;
      return;
    }
  }
  if ((DAT_00ff6004 & 0x10) != 0) {
    FUN_00027f18();
    FUN_00006912();
    FUN_00006928();
    FUN_00001098();
    FUN_00007c14();
    DAT_00ff605f = 0;
    DAT_00ff6085 = 1;
  }
  return;
}

