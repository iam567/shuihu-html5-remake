/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001c09c */

void FUN_0001c09c(void)

{
  short sVar1;
  short sVar2;
  char cVar3;
  char *pcVar4;
  
  FUN_0001a6b0();
  Seed_1028();
  DAT_00ff60c4 = (&DAT_00ffe400)[(short)(ushort)DAT_00ff617a];
  FUN_0000b7fe();
  DAT_00ff60c8 = *(ushort *)(&DAT_0001b418 + (short)((ushort)DAT_00ff60c4 << 1)) >> 1;
  FUN_0001add8();
  FUN_0001add8();
  FUN_0001add8();
  sVar2 = 0;
  sVar1 = 0x7f;
  do {
    if (DAT_00ff60c4 == (&DAT_00ffe400)[sVar2]) {
      DAT_00ff60d0 = (ushort)(byte)(&DAT_00ffe480)[sVar2];
      goto LAB_0001c168;
    }
    sVar2 = sVar2 + 1;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00ff60d0 = 0;
LAB_0001c168:
  FUN_0001add8();
  pcVar4 = &DAT_00ff8000;
  cVar3 = '\0';
  sVar2 = 0x13;
  do {
    if (*pcVar4 == '\0') break;
    if (DAT_00ff60c4 == pcVar4[8]) {
      cVar3 = cVar3 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar4[9]) {
      cVar3 = cVar3 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar4[10]) {
      cVar3 = cVar3 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar4[0xb]) {
      cVar3 = cVar3 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar4[0x26]) {
      cVar3 = cVar3 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar4[0x27]) {
      cVar3 = cVar3 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar4[0x28]) {
      cVar3 = cVar3 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar4[0x29]) {
      cVar3 = cVar3 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar4[0x2a]) {
      cVar3 = cVar3 + '\x01';
    }
    pcVar4 = pcVar4 + 0x40;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  DAT_00ff60d4 = (char)DAT_00ff60d0 + cVar3;
  FUN_0001add8();
  DAT_00ff6189 = DAT_00ff6189 & 0xf9;
  DAT_00ff618e = 0;
LAB_0001c22a:
  do {
    FUN_00000e40();
    FUN_000180e6();
    if ((DAT_00ff6003 & 1) != 0) {
      if ((DAT_00ff6004 & 1) == 0) {
        if (DAT_00ff618c != '\0') {
          DAT_00ff618c = DAT_00ff618c + -1;
          goto LAB_0001c22a;
        }
      }
      else {
        DAT_00ff618c = '\b';
      }
      if ((short)(ushort)DAT_00ff618e < (short)DAT_00ff60d0) {
        FUN_00027f08();
        DAT_00ff618e = DAT_00ff618e + 1;
        FUN_0001add8();
        DAT_00ff60cc = (uint)DAT_00ff618e * (uint)DAT_00ff60c8;
        DAT_00ff6190 = 0x10;
        DAT_00ff6192 = 0xe;
        FUN_0001c476();
      }
      goto LAB_0001c22a;
    }
    if ((DAT_00ff6003 & 2) != 0) {
      if ((DAT_00ff6004 & 2) == 0) {
        if (DAT_00ff618c != '\0') {
          DAT_00ff618c = DAT_00ff618c + -1;
          goto LAB_0001c22a;
        }
      }
      else {
        DAT_00ff618c = '\b';
      }
      if (DAT_00ff618e != 0) {
        DAT_00ff618e = DAT_00ff618e - 1;
        FUN_00027f08();
        FUN_0001b9a8();
        FUN_0001b9a8();
        FUN_0001add8();
        DAT_00ff60cc = (uint)DAT_00ff618e * (uint)DAT_00ff60c8;
        DAT_00ff6190 = 0x10;
        DAT_00ff6192 = 0xe;
        FUN_0001c476();
      }
      goto LAB_0001c22a;
    }
    if ((DAT_00ff6004 & 0x40) == 0) {
      if ((DAT_00ff6004 & 0x10) != 0) {
        FUN_00027f18();
LAB_0001c43e:
        FUN_0001b9a8();
        FUN_0001b76a();
        FUN_0001c036();
        DAT_00ff6189 = DAT_00ff6189 | 6;
        return;
      }
    }
    else if (DAT_00ff618e != 0) {
      DAT_00ffe110 = DAT_00ff60cc + DAT_00ffe110;
      FUN_00027f18();
      sVar2 = 0;
      sVar1 = 0x7f;
      do {
        if (DAT_00ff60c4 == (&DAT_00ffe400)[sVar2]) {
          (&DAT_00ffe480)[sVar2] = (&DAT_00ffe480)[sVar2] - DAT_00ff618e;
          FUN_0001b9a8();
          DAT_00ff6190 = 9;
          DAT_00ff6192 = 2;
          FUN_0001c476();
          goto LAB_0001c43e;
        }
        sVar2 = sVar2 + 1;
        sVar1 = sVar1 + -1;
      } while (sVar1 != -1);
    }
  } while( true );
}

