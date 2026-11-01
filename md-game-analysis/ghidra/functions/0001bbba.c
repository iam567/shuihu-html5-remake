/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001bbba */

void FUN_0001bbba(void)

{
  short sVar1;
  short sVar2;
  char cVar4;
  uint uVar3;
  char *pcVar5;
  
  FUN_0001a6b0();
  Seed_1028();
  DAT_00ff60c4 = (&DAT_00ff9000)[(short)(ushort)DAT_00ff617a];
  FUN_0000b7fe();
  DAT_00ff60c8 = *(ushort *)(&DAT_0001b418 + (short)((ushort)DAT_00ff60c4 << 1));
  FUN_0001add8();
  FUN_0001add8();
  FUN_0001add8();
  sVar2 = 0;
  sVar1 = 0x7f;
  do {
    if (DAT_00ff60c4 == (&DAT_00ffe400)[sVar2]) {
      DAT_00ff60d0 = (ushort)(byte)(&DAT_00ffe480)[sVar2];
      goto LAB_0001bc84;
    }
    sVar2 = sVar2 + 1;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00ff60d0 = 0;
LAB_0001bc84:
  FUN_0001add8();
  pcVar5 = &DAT_00ff8000;
  cVar4 = '\0';
  sVar2 = 0x13;
  do {
    if (*pcVar5 == '\0') break;
    if (DAT_00ff60c4 == pcVar5[8]) {
      cVar4 = cVar4 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar5[9]) {
      cVar4 = cVar4 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar5[10]) {
      cVar4 = cVar4 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar5[0xb]) {
      cVar4 = cVar4 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar5[0x26]) {
      cVar4 = cVar4 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar5[0x27]) {
      cVar4 = cVar4 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar5[0x28]) {
      cVar4 = cVar4 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar5[0x29]) {
      cVar4 = cVar4 + '\x01';
    }
    if (DAT_00ff60c4 == pcVar5[0x2a]) {
      cVar4 = cVar4 + '\x01';
    }
    pcVar5 = pcVar5 + 0x40;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  DAT_00ff60d4 = (char)DAT_00ff60d0 + cVar4;
  FUN_0001add8();
  DAT_00ff6189 = DAT_00ff6189 & 0xf9;
  DAT_00ff618e = 0;
LAB_0001bd46:
  do {
    FUN_00000e40();
    FUN_000180e6();
    if ((DAT_00ff6003 & 1) != 0) {
      if ((DAT_00ff6004 & 1) == 0) {
        if (DAT_00ff618c != '\0') {
          DAT_00ff618c = DAT_00ff618c + -1;
          goto LAB_0001bd46;
        }
      }
      else {
        DAT_00ff618c = '\b';
      }
      uVar3 = (uint)(ushort)(DAT_00ff618e + 1) * (uint)DAT_00ff60c8;
      if ((uVar3 < DAT_00ffe110 || uVar3 - DAT_00ffe110 == 0) &&
         ((byte)(DAT_00ff60d4 + DAT_00ff618e) < 99)) {
        FUN_00027f08();
        DAT_00ff618e = DAT_00ff618e + 1;
        FUN_0001add8();
        DAT_00ff60cc = (uint)DAT_00ff618e * (uint)DAT_00ff60c8;
        DAT_00ff6190 = 0x10;
        DAT_00ff6192 = 0xe;
        FUN_0001c476();
      }
      goto LAB_0001bd46;
    }
    if ((DAT_00ff6003 & 2) != 0) {
      if ((DAT_00ff6004 & 2) == 0) {
        if (DAT_00ff618c != '\0') {
          DAT_00ff618c = DAT_00ff618c + -1;
          goto LAB_0001bd46;
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
      goto LAB_0001bd46;
    }
    if ((DAT_00ff6004 & 0x40) == 0) {
      if ((DAT_00ff6004 & 0x10) != 0) {
        FUN_00027f18();
LAB_0001bf82:
        FUN_0001b9a8();
        FUN_0001b76a();
        FUN_0001b9d8();
        DAT_00ff6189 = DAT_00ff6189 | 6;
        return;
      }
    }
    else {
      FUN_00027f18();
      if (DAT_00ff618e != 0) {
        DAT_00ffe110 = DAT_00ffe110 - DAT_00ff60cc;
        sVar2 = 0;
        sVar1 = 0x7f;
        do {
          if (DAT_00ff60c4 == (&DAT_00ffe400)[sVar2]) {
LAB_0001bf2c:
            (&DAT_00ffe480)[sVar2] = DAT_00ff618e + (&DAT_00ffe480)[sVar2];
            FUN_0001b9a8();
            DAT_00ff6190 = 9;
            DAT_00ff6192 = 2;
            FUN_0001c476();
            goto LAB_0001bf82;
          }
          if ((&DAT_00ffe400)[sVar2] == '\0') {
            (&DAT_00ffe400)[sVar2] = DAT_00ff60c4;
            goto LAB_0001bf2c;
          }
          sVar2 = sVar2 + 1;
          sVar1 = sVar1 + -1;
        } while (sVar1 != -1);
      }
    }
  } while( true );
}

