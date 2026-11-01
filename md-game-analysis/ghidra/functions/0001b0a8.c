/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001b0a8 */

void FUN_0001b0a8(void)

{
  short sVar1;
  int iVar2;
  char *pcVar3;
  bool bVar4;
  
  DAT_00ff618a = '\0';
  sVar1 = 0x7f;
  pcVar3 = &DAT_00ffe400;
  do {
    if (*pcVar3 == '\0') break;
    DAT_00ff618a = DAT_00ff618a + '\x01';
    sVar1 = sVar1 + -1;
    pcVar3 = pcVar3 + 1;
  } while (sVar1 != -1);
  if (DAT_00ff618a == '\0') {
    return;
  }
  DAT_00ff617f = '\0';
  FUN_0001bfba();
  DAT_00ff617a = 0;
  DAT_00ff618b = 0;
  FUN_0001b6e8();
  FUN_0001b330();
  DAT_00ff6178 = 0xc0;
  DAT_00ff6188 = DAT_00ff6188 | 2;
  DAT_00ff6189 = DAT_00ff6189 | 0xe;
LAB_0001b122:
  do {
    FUN_00000e40();
    FUN_000180e6();
    if ((DAT_00ff6003 & 1) == 0) {
      if ((DAT_00ff6003 & 2) == 0) {
        if ((DAT_00ff6004 & 0x40) == 0) {
          if ((DAT_00ff6004 & 0x10) != 0) {
            FUN_00027f18();
            DAT_00ff6189 = DAT_00ff6189 & 0xf1;
            DAT_00ff6188 = DAT_00ff6188 & 0xfd;
            FUN_0001977c();
            DAT_00ff618b = 0;
            FUN_0001b76a();
            FUN_0001b9a8();
            DAT_00ff801d = 1;
            sVar1 = 0x12;
            iVar2 = 0xff8000;
            do {
              *(undefined1 *)(iVar2 + 0x5d) = 1;
              sVar1 = sVar1 + -1;
              iVar2 = iVar2 + 0x40;
            } while (sVar1 != -1);
            return;
          }
        }
        else {
          FUN_00027f18();
          FUN_0001c09c();
        }
        goto LAB_0001b122;
      }
      if ((DAT_00ff6004 & 2) == 0) {
        if (DAT_00ff618c != '\0') {
          DAT_00ff618c = DAT_00ff618c + -1;
          goto LAB_0001b122;
        }
      }
      else {
        DAT_00ff618c = '\b';
      }
      if (DAT_00ff617a < (byte)(DAT_00ff618a - 1U)) {
        DAT_00ff617a = DAT_00ff617a + 1;
        FUN_00027f08();
        FUN_0001b6e8();
        FUN_0001b330();
        if (DAT_00ff6178 == 0x120) {
          DAT_00ff618d = DAT_00ff617f;
          DAT_00ff617f = DAT_00ff617f + '\x01';
          DAT_00ff618b = DAT_00ff618b + 1;
          if (7 < DAT_00ff618b) {
            DAT_00ff618b = 0;
          }
          FUN_0001b954();
          FUN_0001b76a();
          FUN_0001c036();
        }
        else {
          DAT_00ff6178 = DAT_00ff6178 + 0x10;
        }
      }
      goto LAB_0001b122;
    }
    if ((DAT_00ff6004 & 1) == 0) {
      if (DAT_00ff618c != '\0') {
        DAT_00ff618c = DAT_00ff618c + -1;
        goto LAB_0001b122;
      }
    }
    else {
      DAT_00ff618c = '\b';
    }
    if (DAT_00ff617a != 0) {
      DAT_00ff617a = DAT_00ff617a - 1;
      FUN_00027f08();
      FUN_0001b6e8();
      FUN_0001b330();
      if (DAT_00ff6178 == 0xc0) {
        DAT_00ff618d = DAT_00ff617f;
        DAT_00ff617f = DAT_00ff617f + -1;
        bVar4 = DAT_00ff618b == 0;
        DAT_00ff618b = DAT_00ff618b - 1;
        if (bVar4) {
          DAT_00ff618b = 7;
        }
        FUN_0001b954();
        FUN_0001b76a();
        FUN_0001c036();
      }
      else {
        DAT_00ff6178 = DAT_00ff6178 + -0x10;
      }
    }
  } while( true );
}

