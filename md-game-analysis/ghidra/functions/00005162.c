/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00005162 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00005162(void)

{
  ushort uVar1;
  int iVar2;
  undefined2 uVar3;
  short sVar4;
  byte bVar5;
  char *pcVar6;
  
  if ((DAT_00ff6004 & 0x40) == 0) {
    if ((DAT_00ff6004 & 0x10) == 0) {
      if ((DAT_00ff6004 & 0x20) == 0) {
        if ((DAT_00ff6003 & 4) == 0) {
          if ((DAT_00ff6003 & 8) == 0) {
            if ((DAT_00ff6003 & 1) == 0) {
              if ((DAT_00ff6003 & 2) != 0) {
                iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
                if (*(char *)((int)&DAT_00ffe784 + iVar2 + 2) != '\x01') {
                  DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
                }
                *(undefined1 *)((int)&DAT_00ffe784 + iVar2 + 2) = 1;
                *(undefined1 *)((int)&DAT_00ffe780 + iVar2 + 1) = 4;
                sVar4 = (*(ushort *)((int)&DAT_00ffe784 + iVar2) >> 5) + 1;
                if (((((char)sVar4 < DAT_00ffe107) &&
                     (sVar4 = (*(ushort *)((int)&DAT_00ffe780 + iVar2 + 2) >> 5) +
                              (ushort)DAT_00ffe106 * sVar4,
                     (byte)(&DAT_00ffd000)[sVar4] < DAT_00ff610f)) &&
                    (*(byte *)((int)&DAT_00ffb000 + (int)sVar4) < 0x7f)) &&
                   (sVar4 = (*(short *)((int)&DAT_00ffe784 + iVar2) + 0x80) - DAT_00ff6016,
                   sVar4 < 0x140)) {
                  if ((0xdf < sVar4) && (DAT_00ffe105 < (byte)(DAT_00ffe107 - 7U))) {
                    DAT_00ffe105 = DAT_00ffe105 + 1;
                    DAT_00ff615c = DAT_00ff615c | 2;
                    FUN_000032f2();
                    DAT_00ff6038 = 1;
                    DAT_00ff6039 = 0x20;
                  }
                  DAT_00ff606a = 0x20;
                }
              }
            }
            else {
              iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
              if (*(char *)((int)&DAT_00ffe784 + iVar2 + 2) != '\0') {
                DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
              }
              *(undefined1 *)((int)&DAT_00ffe784 + iVar2 + 2) = 0;
              *(undefined1 *)((int)&DAT_00ffe780 + iVar2 + 1) = 0;
              if (((*(short *)((int)&DAT_00ffe784 + iVar2) != 0) &&
                  (sVar4 = (*(ushort *)((int)&DAT_00ffe780 + iVar2 + 2) >> 5) +
                           (ushort)DAT_00ffe106 *
                           ((*(ushort *)((int)&DAT_00ffe784 + iVar2) >> 5) - 1),
                  (byte)(&DAT_00ffd000)[sVar4] < DAT_00ff610f)) &&
                 ((*(byte *)((int)&DAT_00ffb000 + (int)sVar4) < 0x7f &&
                  (uVar1 = (*(short *)((int)&DAT_00ffe784 + iVar2) + 0x80) - DAT_00ff6016,
                  0x80 < uVar1)))) {
                if ((uVar1 < 0xe1) && (DAT_00ffe105 != 0)) {
                  DAT_00ffe105 = DAT_00ffe105 - 1;
                  DAT_00ff615c = DAT_00ff615c | 1;
                  FUN_000032c4();
                  DAT_00ff6038 = 0;
                  DAT_00ff6039 = 0x20;
                }
                DAT_00ff606a = 0x20;
              }
            }
          }
          else {
            iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
            if (*(char *)((int)&DAT_00ffe784 + iVar2 + 2) != '\x03') {
              DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
            }
            *(undefined1 *)((int)&DAT_00ffe784 + iVar2 + 2) = 3;
            *(undefined1 *)((int)&DAT_00ffe780 + iVar2 + 1) = 0xc;
            sVar4 = (*(ushort *)((int)&DAT_00ffe780 + iVar2 + 2) >> 5) + 1;
            if (((((char)sVar4 < (char)DAT_00ffe106) &&
                 (sVar4 = sVar4 + (ushort)DAT_00ffe106 *
                                  (*(ushort *)((int)&DAT_00ffe784 + iVar2) >> 5),
                 (byte)(&DAT_00ffd000)[sVar4] < DAT_00ff610f)) &&
                (*(byte *)((int)&DAT_00ffb000 + (int)sVar4) < 0x7f)) &&
               (sVar4 = (*(short *)((int)&DAT_00ffe780 + iVar2 + 2) + 0x80) - DAT_00ff6014,
               sVar4 < 0x1a0)) {
              if ((0x11f < sVar4) && (DAT_00ffe104 < (byte)(DAT_00ffe106 - 10))) {
                DAT_00ffe104 = DAT_00ffe104 + 1;
                DAT_00ff615c = DAT_00ff615c | 8;
                FUN_00003354();
                DAT_00ff6038 = 3;
                DAT_00ff6039 = 0x20;
              }
              DAT_00ff606a = 0x20;
            }
          }
        }
        else {
          iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
          if (*(char *)((int)&DAT_00ffe784 + iVar2 + 2) != '\x02') {
            DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
          }
          *(undefined1 *)((int)&DAT_00ffe784 + iVar2 + 2) = 2;
          *(undefined1 *)((int)&DAT_00ffe780 + iVar2 + 1) = 8;
          if (((*(short *)((int)&DAT_00ffe780 + iVar2 + 2) != 0) &&
              (sVar4 = ((*(ushort *)((int)&DAT_00ffe780 + iVar2 + 2) >> 5) - 1) +
                       (ushort)DAT_00ffe106 * (*(ushort *)((int)&DAT_00ffe784 + iVar2) >> 5),
              (byte)(&DAT_00ffd000)[sVar4] < DAT_00ff610f)) &&
             ((*(byte *)((int)&DAT_00ffb000 + (int)sVar4) < 0x7f &&
              (uVar1 = (*(short *)((int)&DAT_00ffe780 + iVar2 + 2) + 0x80) - DAT_00ff6014,
              0x80 < uVar1)))) {
            if ((uVar1 < 0x101) && (DAT_00ffe104 != 0)) {
              DAT_00ffe104 = DAT_00ffe104 - 1;
              DAT_00ff615c = DAT_00ff615c | 4;
              FUN_00003326();
              DAT_00ff6038 = 2;
              DAT_00ff6039 = 0x20;
            }
            DAT_00ff606a = 0x20;
          }
        }
      }
    }
    else {
      FUN_00027f18();
      FUN_00006912();
      FUN_00006928();
      FUN_00001098();
      iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
      *(undefined1 *)((int)&DAT_00ffe784 + iVar2 + 2) = 1;
      uVar3 = DAT_00ff608c;
      DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
      _DAT_00ffe1f0 = *(int *)((int)&DAT_00ffe780 + iVar2 + 2);
      *(undefined2 *)((int)&DAT_00ffe780 + iVar2 + 2) = DAT_00ff608a;
      *(undefined2 *)((int)&DAT_00ffe784 + iVar2) = uVar3;
      FUN_00007c14();
      DAT_00ff6085 = 1;
    }
  }
  else {
    iVar2 = *(int *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2);
    bVar5 = 0;
    pcVar6 = (char *)&DAT_00ffe780;
    sVar4 = 0x1d;
    do {
      if (((*pcVar6 != '\0') && (bVar5 != DAT_00ff606b)) && (iVar2 == *(int *)(pcVar6 + 2))) {
        return;
      }
      bVar5 = bVar5 + 1;
      pcVar6 = pcVar6 + 0x40;
      sVar4 = sVar4 + -1;
    } while (sVar4 != -1);
    _DAT_00ffe1f0 = iVar2;
    *(undefined1 *)((int)&DAT_00ffe784 + (short)((ushort)DAT_00ff606b << 6) + 2) = 1;
    DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
    FUN_00027f18();
    FUN_00006912();
    FUN_00001098();
    DAT_00ff6085 = 1;
    DAT_00ff606c = 0x1d;
    DAT_00ff605f = 0;
  }
  return;
}

