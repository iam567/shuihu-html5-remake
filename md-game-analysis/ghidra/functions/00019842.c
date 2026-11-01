/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00019842 */

void FUN_00019842(void)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  short sVar6;
  ushort uVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  
  iVar5 = (int)(short)((ushort)(byte)((&DAT_00ffe610)[(short)(ushort)DAT_00ff615b] - 1) << 4);
  if (DAT_00ff6177 == '\0') {
    cVar4 = *(char *)((int)&DAT_00ffe63a + iVar5);
  }
  else if (DAT_00ff6177 == '\x01') {
    cVar4 = *(char *)((int)&DAT_00ffe632 + iVar5);
  }
  else {
    cVar4 = (&DAT_00ffe639)[iVar5];
  }
  if (cVar4 != '\0') {
    DAT_00ff617e = 1;
    DAT_00ff617c = 0x170;
    DAT_00ff615d = DAT_00ff615d & 0xfe;
    DAT_00ff615d = DAT_00ff615d | 0x20;
    DAT_00ff617a = 0;
    DAT_00ff6178 = 0x98;
    FUN_00019bfe();
LAB_000198d2:
    do {
      while( true ) {
        FUN_00000e40();
        FUN_000180e6();
        if (DAT_00ff6177 == '\x02') break;
        if ((DAT_00ff6004 & 1) == 0) {
          if ((DAT_00ff6004 & 2) == 0) break;
          FUN_00027f08();
          DAT_00ff617a = DAT_00ff617a + 1;
          if (3 < DAT_00ff617a) {
            DAT_00ff617a = 0;
          }
        }
        else {
          FUN_00027f08();
          bVar10 = DAT_00ff617a == 0;
          DAT_00ff617a = DAT_00ff617a - 1;
          if (bVar10) {
            DAT_00ff617a = 3;
          }
        }
        DAT_00ff6178 = (ushort)DAT_00ff617a * 0x10 + 0x98;
        FUN_00019bfe();
      }
      if ((DAT_00ff6004 & 0x40) != 0) {
        FUN_00027fa8();
        if ((DAT_00ff617a != 0) || (DAT_00ff6177 != '\0')) {
          FUN_00027f18();
          sVar6 = 10;
          if ((DAT_00ff6177 != '\0') && (sVar6 = 2, DAT_00ff6177 != '\x01')) {
            sVar6 = 9;
          }
          pcVar8 = &DAT_00ffe630 +
                   (int)sVar6 +
                   (int)(short)((ushort)(byte)((&DAT_00ffe610)[(short)(ushort)DAT_00ff615b] - 1) <<
                               4);
          cVar4 = pcVar8[(short)(ushort)DAT_00ff617a];
          pcVar8[(short)(ushort)DAT_00ff617a] = '\0';
          if (DAT_00ff6177 != '\x02') {
            cVar1 = pcVar8[1];
            cVar2 = pcVar8[2];
            cVar3 = pcVar8[3];
            pcVar8[0] = '\0';
            pcVar8[1] = '\0';
            pcVar8[2] = '\0';
            pcVar8[3] = '\0';
            pcVar9 = pcVar8;
            if (*pcVar8 != '\0') {
              pcVar9 = pcVar8 + 1;
              *pcVar8 = *pcVar8;
            }
            pcVar8 = pcVar9;
            if (cVar1 != '\0') {
              pcVar8 = pcVar9 + 1;
              *pcVar9 = cVar1;
            }
            pcVar9 = pcVar8;
            if (cVar2 != '\0') {
              pcVar9 = pcVar8 + 1;
              *pcVar8 = cVar2;
            }
            if (cVar3 != '\0') {
              *pcVar9 = cVar3;
            }
          }
          if (cVar4 != '\0') {
            uVar7 = (ushort)DAT_00ff617b;
            (&DAT_00ffe400)[(short)uVar7] = cVar4;
            (&DAT_00ffe480)[(short)uVar7] = (&DAT_00ffe480)[(short)uVar7] + '\x01';
            FUN_00019670();
            FUN_00019bfe();
          }
        }
        goto LAB_000198d2;
      }
    } while ((DAT_00ff6004 & 0x10) == 0);
    FUN_00027f18();
    DAT_00ff615d = DAT_00ff615d & 0xdf;
    DAT_00ff615d = DAT_00ff615d | 1;
    DAT_00ff617e = 2;
    DAT_00ff617c = 0x140;
    FUN_0001977c();
    Seed_1060();
  }
  return;
}

