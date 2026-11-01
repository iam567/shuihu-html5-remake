/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000dbf0 */

void FUN_0000dbf0(void)

{
  char cVar1;
  int iVar2;
  ushort uVar3;
  short extraout_D1w;
  short sVar4;
  
  if (((((DAT_00ffe1f7 == '\x01') && ((DAT_00ff603d & 1) == 0)) && (DAT_00ff6039 == '\0')) &&
      ((DAT_00ff604c == '\0' && (DAT_00ff606a == '\0')))) &&
     ((DAT_00ff606e == '\0' && (DAT_00ff611c == '\0')))) {
    if (DAT_00ff6085 == '\0') {
      FUN_0000db8c();
      return;
    }
    if (DAT_00ff6085 == '\x01') {
      if (DAT_00ff605a == '\0') {
        iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
        if (*(char *)((int)&DAT_00ffe78c + iVar2) == '\0') {
          if ((0x1e < (ushort)(((uint)*(ushort *)((int)&DAT_00ffe792 + iVar2) * 100) /
                              (uint)*(ushort *)((int)&DAT_00ffe79e + iVar2))) ||
             (((&DAT_00ffe7a7)[iVar2] != '\0' &&
              (*(char *)((int)&PTR_DAT_00028e5b +
                        (int)(short)((ushort)(byte)((&DAT_00ffe7a7)[iVar2] - 1) << 3)) == '\x02'))))
          {
            FUN_0000e47c();
            return;
          }
          DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
          *(undefined1 *)((int)&DAT_00ffe780 + iVar2 + 1) = 4;
          *(undefined1 *)((int)&DAT_00ffe784 + iVar2 + 2) = 1;
          FUN_00027f48();
          (&DAT_00ffe79d)[iVar2] = 0x60;
          DAT_00ff6094 = *(undefined2 *)((int)&DAT_00ffe792 + iVar2);
          DAT_00ff6096 = *(undefined2 *)((int)&DAT_00ffe79e + iVar2);
          DAT_00ff609a = 0x60;
          DAT_00ff609d = 1;
          DAT_00ff6152 = *(ushort *)((int)&DAT_00ffe79e + iVar2) >> 3;
          DAT_00ff6098 = DAT_00ff6152 + *(short *)((int)&DAT_00ffe792 + iVar2);
          if (*(ushort *)((int)&DAT_00ffe79e + iVar2) < DAT_00ff6098) {
            DAT_00ff6098 = *(ushort *)((int)&DAT_00ffe79e + iVar2);
          }
          *(ushort *)((int)&DAT_00ffe792 + iVar2) = DAT_00ff6098;
          DAT_00ff60a0 = 0;
          DAT_00ff60a2 = 0x1c;
          DAT_00ff60a4 = 0xd;
          DAT_00ff60a6 = 0x10;
          Seed_e50();
          FUN_00009c4a();
          DAT_00ff60aa = 0xff;
          DAT_00ff60ab = 7;
          DAT_00ffe1e0 = DAT_00ffe1e0 & ~(1 << (DAT_00ff606b & 0x1f));
          DAT_00ff6085 = '\b';
        }
        else {
          DAT_00ff6085 = '\f';
          DAT_00ff60c8 = 2;
          FUN_0000ca16();
          DAT_00ff6107 = 0x3c;
        }
      }
    }
    else if (DAT_00ff6085 == '\x02') {
      DAT_00ffe1e0 = DAT_00ffe1e0 & ~(1 << (DAT_00ff606b & 0x1f));
      DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
      iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
      *(undefined1 *)((int)&DAT_00ffe780 + iVar2 + 1) = 4;
      *(undefined1 *)((int)&DAT_00ffe784 + iVar2 + 2) = 1;
      DAT_00ffe1f0 = *(undefined2 *)((int)&DAT_00ffe780 + iVar2 + 2);
      DAT_00ffe1f2 = *(undefined2 *)((int)&DAT_00ffe784 + iVar2);
      FUN_00006928();
      FUN_00001098();
      DAT_00ff6085 = '\x03';
    }
    else if (DAT_00ff6085 == '\x03') {
      if (DAT_00ff60a8 < 8) {
        if (DAT_00ff60a8 < 6) {
          if (3 < DAT_00ff60a8) {
            FUN_0000a718();
            FUN_000092f8();
            if (DAT_00ff60bd != 0xff) {
              FUN_00006912();
              FUN_0000a596();
              FUN_00006c86();
              DAT_00ff6052 = *(ushort *)
                              ((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff60bd << 6) + 2) >> 5;
              DAT_00ff6054 = *(ushort *)
                              ((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff60bd << 6)) >> 5;
              DAT_00ff605a = 1;
              DAT_00ff6085 = 4;
              return;
            }
            DAT_00ff60a8 = 3;
          }
        }
        else {
          FUN_0000cbb0();
          FUN_0000cdd0();
          if (DAT_00ff6108 != 0xff) {
            FUN_00006912();
            FUN_0000a596();
            FUN_00006c86();
            DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff6108 << 6) + 2)
                           >> 5;
            DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff6108 << 6))
                           >> 5;
            DAT_00ff605a = 1;
            DAT_00ff6085 = 4;
            return;
          }
          DAT_00ff60a8 = 3;
        }
      }
      else {
        FUN_0000916c();
        FUN_0000d85c();
        FUN_0000d3d2();
        if (DAT_00ff610b != 0xff) {
          FUN_00006912();
          FUN_0000d34a();
          FUN_00006c86();
          DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff610b << 6) + 2) >>
                         5;
          DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff610b << 6))
                         >> 5;
          DAT_00ff605a = 1;
          DAT_00ff6085 = 4;
          return;
        }
        DAT_00ff60a8 = 3;
      }
      if (DAT_00ff60a8 < 2) {
        FUN_00006912();
      }
      else {
        FUN_0000d78e();
        FUN_00006912();
        if (DAT_00ff7180 != -1) {
          FUN_00009b32();
          FUN_00006c86();
          FUN_00009192();
          DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + (short)(extraout_D1w << 6) + 2) >> 5;
          DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)(extraout_D1w << 6)) >> 5;
          DAT_00ff605a = 1;
          DAT_00ff6085 = 4;
          return;
        }
      }
      DAT_00ff6085 = '\0';
      DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
      uVar3 = (ushort)DAT_00ff606b;
      *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar3 << 6) + 1) = 0x10;
      *(undefined1 *)((int)&DAT_00ffe784 + (short)(uVar3 << 6) + 2) = 1;
    }
    else if (DAT_00ff6085 == '\x04') {
      if (DAT_00ff605a == '\0') {
        FUN_00006912();
        FUN_00001098();
        if (DAT_00ff60a8 < 8) {
          if (DAT_00ff60a8 < 6) {
            if (DAT_00ff60a8 < 4) {
              FUN_00009c4a();
              FUN_00008738();
              FUN_0000e966();
              DAT_00ff6085 = '\x05';
            }
            else {
              FUN_0000e8ba();
              DAT_00ff6085 = '\b';
            }
          }
          else {
            FUN_0000cf04();
            DAT_00ff6085 = '\r';
          }
        }
        else {
          FUN_0000d688();
          DAT_00ff6085 = '\r';
        }
      }
    }
    else if (DAT_00ff6085 == '\x05') {
      FUN_0000ea8c();
    }
    else if (DAT_00ff6085 == '\x06') {
      if ((DAT_00ff6019 & 4) == 0) {
        FUN_00027f68();
        sVar4 = (ushort)DAT_00ff609f << 6;
        *(undefined1 *)((int)&DAT_00ffe780 + (int)sVar4) = 0;
        if ((&DAT_00ffe7aa)[sVar4] == '{') {
          DAT_00ff6156 = (&DAT_00ffe794)[sVar4];
          FUN_000170ae();
        }
        else {
          DAT_00ff630c = (*(short *)((int)&DAT_00ffe780 + sVar4 + 2) - DAT_00ff6014) + 0x80;
          DAT_00ff630e = (*(short *)((int)&DAT_00ffe784 + (int)sVar4) - DAT_00ff6016) + 0x80;
          FUN_00016950();
          DAT_00ff6301 = 0;
          Seed_e50();
          DAT_00ff6310 = '\x01';
          DAT_00ff6300 = DAT_00ff6300 | 1;
        }
        DAT_00ff6085 = '\a';
      }
    }
    else if ((DAT_00ff6085 == '\a') && (DAT_00ff6310 == '\0')) {
      DAT_00ff6085 = '\0';
      DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
      uVar3 = (ushort)DAT_00ff606b;
      *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar3 << 6) + 1) = 0x10;
      *(undefined1 *)((int)&DAT_00ffe784 + (short)(uVar3 << 6) + 2) = 1;
    }
    else if (DAT_00ff6085 == '\b') {
      FUN_0000eb74();
    }
    else if (DAT_00ff6085 == '\t') {
      FUN_0000b4a8();
    }
    else if (DAT_00ff6085 == '\n') {
      FUN_0000ebbe();
    }
    else if (DAT_00ff6085 == '\v') {
      if ((DAT_00ff6019 & 4) == 0) {
        FUN_00027f68();
        sVar4 = (ushort)DAT_00ff606b << 6;
        *(undefined1 *)((int)&DAT_00ffe780 + (int)sVar4) = 0;
        DAT_00ff630c = (*(short *)((int)&DAT_00ffe780 + sVar4 + 2) - DAT_00ff6014) + 0x80;
        DAT_00ff630e = (*(short *)((int)&DAT_00ffe784 + (int)sVar4) - DAT_00ff6016) + 0x80;
        FUN_00016950();
        DAT_00ff6301 = 0;
        Seed_e50();
        DAT_00ff6310 = '\x01';
        DAT_00ff6300 = DAT_00ff6300 | 1;
        DAT_00ff6085 = '\a';
      }
    }
    else if (DAT_00ff6085 == '\f') {
      if (DAT_00ff6107 == 0) {
        DAT_00ff6085 = '\0';
        DAT_00ffe1e0 = DAT_00ffe1e0 & ~(1 << (DAT_00ff606b & 0x1f));
        DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
        uVar3 = (ushort)DAT_00ff606b;
        *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar3 << 6) + 1) = 0x10;
        *(undefined1 *)((int)&DAT_00ffe784 + (short)(uVar3 << 6) + 2) = 1;
      }
      else {
        DAT_00ff6107 = DAT_00ff6107 - 1;
        if (DAT_00ff6107 == 0) {
          FUN_00001098();
        }
      }
    }
    else if (DAT_00ff6085 == '\r') {
      if (DAT_00ff6107 == 0) {
        DAT_00ff60aa = 0;
        FUN_00001098();
        DAT_00ff6085 = '\0';
        DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
        uVar3 = (ushort)DAT_00ff606b;
        *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar3 << 6) + 1) = 0x10;
        *(undefined1 *)((int)&DAT_00ffe784 + (short)(uVar3 << 6) + 2) = 1;
      }
      else {
        DAT_00ff6107 = DAT_00ff6107 - 1;
      }
    }
    else if (DAT_00ff6085 == '\x0e') {
      if (DAT_00ff6107 == 0x20) {
        DAT_00ff606e = '\x01';
        DAT_00ff6078 = &DAT_00ffa000;
        DAT_00ff6085 = '\x02';
      }
      else {
        uVar3 = (ushort)DAT_00ff606b;
        cVar1 = (&DAT_00008734)[(short)(ushort)(DAT_00ff6107 >> 3)];
        *(char *)((int)&DAT_00ffe784 + (short)(uVar3 << 6) + 2) = cVar1;
        *(char *)((int)&DAT_00ffe780 + (short)(uVar3 << 6) + 1) = cVar1 << 2;
        DAT_00ff6107 = DAT_00ff6107 + 1;
      }
    }
  }
  return;
}

