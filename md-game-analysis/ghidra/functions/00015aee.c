/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00015aee */

void FUN_00015aee(void)

{
  undefined4 uVar1;
  int iVar2;
  ushort uVar3;
  byte bVar4;
  char cVar5;
  char *pcVar6;
  char *pcVar7;
  
  if (DAT_00ff7180 != 0xff) {
    if ((DAT_00ff6004 & 0x40) != 0) {
      FUN_00001098();
      DAT_00ffe1e0 = DAT_00ffe1e0 & ~(1 << (DAT_00ff606b & 0x1f));
      DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
      iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
      *(undefined1 *)((int)&DAT_00ffe780 + iVar2 + 1) = 4;
      *(undefined1 *)((int)&DAT_00ffe784 + iVar2 + 2) = 1;
      *(undefined1 *)((int)&DAT_00ffe788 + (short)(ushort)DAT_00ff60b7 + iVar2) = 0;
      uVar1 = *(undefined4 *)((int)&DAT_00ffe788 + iVar2);
      *(undefined4 *)((int)&DAT_00ffe788 + iVar2) = 0;
      pcVar6 = (char *)((int)&DAT_00ffe788 + iVar2);
      if ((char)uVar1 != '\0') {
        pcVar6 = (char *)((int)&DAT_00ffe788 + iVar2 + 1);
        *(char *)((int)&DAT_00ffe788 + iVar2) = (char)uVar1;
      }
      cVar5 = (char)((uint)uVar1 >> 8);
      pcVar7 = pcVar6;
      if (cVar5 != '\0') {
        pcVar7 = pcVar6 + 1;
        *pcVar6 = cVar5;
      }
      cVar5 = (char)((uint)uVar1 >> 0x10);
      pcVar6 = pcVar7;
      if (cVar5 != '\0') {
        pcVar6 = pcVar7 + 1;
        *pcVar7 = cVar5;
      }
      cVar5 = (char)((uint)uVar1 >> 0x18);
      if (cVar5 != '\0') {
        *pcVar6 = cVar5;
      }
      DAT_00ff609f = (&DAT_00ff7180)[(short)(ushort)DAT_00ff6087];
      if (DAT_00ff60bb == '\0') {
        FUN_0000a5fe();
        DAT_00ff6085 = 6;
      }
      else if (DAT_00ff60bb == '\x01') {
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
      else if (DAT_00ff60bb == '\x02') {
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
      else if (DAT_00ff60bb == '\x03') {
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
      else if (DAT_00ff60bb == '\x04') {
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
      else if (DAT_00ff60bb == '\x06') {
        uVar3 = (ushort)DAT_00ff609f;
        (&DAT_00ffe79d)[(short)(uVar3 << 6)] = 0x60;
        *(undefined1 *)((int)&DAT_00ffe78c + (short)(uVar3 << 6) + 2) = 3;
        DAT_00ff6109 = 7;
        FUN_00014ff2();
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == '\a') {
        uVar3 = (ushort)DAT_00ff609f;
        (&DAT_00ffe79d)[(short)(uVar3 << 6)] = 0x60;
        *(undefined1 *)((int)&DAT_00ffe78c + (short)(uVar3 << 6) + 3) = 3;
        DAT_00ff6109 = 8;
        FUN_00014ff2();
        DAT_00ff610a = 0x60;
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6107 = 0x60;
        DAT_00ff6085 = 0xf;
        FUN_00027f48();
      }
      else if (DAT_00ff60bb == '\b') {
        FUN_00015f46();
        DAT_00ff60b2 = 0;
        DAT_00ff6085 = 5;
      }
      FUN_00006912();
      FUN_00006928();
      return;
    }
    if ((DAT_00ff6004 & 0xf) != 0) {
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
    FUN_00006912();
    FUN_00006928();
    FUN_00001098();
    FUN_00007c14();
    DAT_00ff605f = 0;
    DAT_00ff6085 = 1;
  }
  return;
}

