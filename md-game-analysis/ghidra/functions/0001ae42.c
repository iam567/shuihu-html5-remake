/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001ae42 */

void FUN_0001ae42(void)

{
  short sVar1;
  int iVar2;
  bool bVar3;
  
  FUN_0001b538();
  DAT_00ff617f = '\0';
  FUN_0001b62e();
  DAT_00ff617a = 0;
  DAT_00ff618b = 0;
  FUN_0001b6e8();
  FUN_0001b74e();
  DAT_00ff6178 = 0xc0;
  DAT_00ff6188 = DAT_00ff6188 | 2;
  DAT_00ff6189 = DAT_00ff6189 | 0xe;
LAB_0001ae9a:
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
            iVar2 = 0xff8000;
            sVar1 = 0x13;
            do {
              *(undefined1 *)(iVar2 + 0x1d) = 1;
              iVar2 = iVar2 + 0x40;
              sVar1 = sVar1 + -1;
            } while (sVar1 != -1);
            return;
          }
        }
        else {
          FUN_00027f18();
          FUN_0001bbba();
        }
        goto LAB_0001ae9a;
      }
      if ((DAT_00ff6004 & 2) == 0) {
        if (DAT_00ff618c != '\0') {
          DAT_00ff618c = DAT_00ff618c + -1;
          goto LAB_0001ae9a;
        }
      }
      else {
        DAT_00ff618c = '\b';
      }
      if (DAT_00ff617a < (byte)(DAT_00ff618a - 1U)) {
        DAT_00ff617a = DAT_00ff617a + 1;
        FUN_00027f08();
        FUN_0001b6e8();
        FUN_0001b74e();
        if (DAT_00ff6178 == 0x120) {
          DAT_00ff618d = DAT_00ff617f;
          DAT_00ff617f = DAT_00ff617f + '\x01';
          DAT_00ff618b = DAT_00ff618b + 1;
          if (7 < DAT_00ff618b) {
            DAT_00ff618b = 0;
          }
          FUN_0001b954();
          FUN_0001b76a();
          FUN_0001b9d8();
        }
        else {
          DAT_00ff6178 = DAT_00ff6178 + 0x10;
        }
      }
      goto LAB_0001ae9a;
    }
    if ((DAT_00ff6004 & 1) == 0) {
      if (DAT_00ff618c != '\0') {
        DAT_00ff618c = DAT_00ff618c + -1;
        goto LAB_0001ae9a;
      }
    }
    else {
      DAT_00ff618c = '\b';
    }
    if (DAT_00ff617a != 0) {
      DAT_00ff617a = DAT_00ff617a - 1;
      FUN_00027f08();
      FUN_0001b6e8();
      FUN_0001b74e();
      if (DAT_00ff6178 == 0xc0) {
        DAT_00ff618d = DAT_00ff617f;
        DAT_00ff617f = DAT_00ff617f + -1;
        bVar3 = DAT_00ff618b == 0;
        DAT_00ff618b = DAT_00ff618b - 1;
        if (bVar3) {
          DAT_00ff618b = 7;
        }
        FUN_0001b954();
        FUN_0001b76a();
        FUN_0001b9d8();
      }
      else {
        DAT_00ff6178 = DAT_00ff6178 + -0x10;
      }
    }
  } while( true );
}

