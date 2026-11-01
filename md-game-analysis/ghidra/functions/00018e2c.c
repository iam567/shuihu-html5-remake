/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00018e2c */

void FUN_00018e2c(void)

{
  byte bVar1;
  short sVar2;
  undefined2 *puVar3;
  bool bVar4;
  
  DAT_00ff6036 = 0;
  FUN_00000ef0();
  DAT_00ff615a = DAT_00ff6018;
  DAT_00ff6018 = 0;
  DAT_00ffe116 = 0xff;
  FUN_00001098();
  FUN_000010ac();
  FUN_000010c8();
  DAT_00ff615d = DAT_00ff615d | 8;
  sVar2 = 0x12;
  puVar3 = &DAT_00017608;
  do {
    Ram00c00004 = *puVar3;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
  } while (sVar2 != -1);
  Ram00c00004 = 0x74000003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x74020003;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40000010;
  Ram00c00000 = 0;
  Ram00c00004 = 0x40020010;
  Ram00c00000 = 0;
  DAT_00ff600a = 0;
  DAT_00ff6034 = 0;
  DAT_00ff6035 = 0;
  FUN_000010e0();
  FUN_00000e40();
  Seed_e50();
  Seed_e50();
  Seed_e50();
  Seed_e50();
  FUN_0001977c();
  Seed_1028();
  Seed_1060();
  DAT_00ff615b = '\0';
  FUN_000192cc();
  DAT_00ff6176 = 0;
  DAT_00ff6177 = 0;
  FUN_000180e6();
  FUN_00000e7c();
  while( true ) {
    while( true ) {
      FUN_00000e40();
      FUN_000180e6();
      if ((DAT_00ff6004 & 0xf) == 0) break;
      FUN_00027f08();
      DAT_00ff6176 = DAT_00ff6176 ^ 1;
    }
    if ((DAT_00ff6004 & 0x10) != 0) break;
    if ((DAT_00ff6004 & 0x40) != 0) {
      FUN_00027f18();
      FUN_00019670();
      bVar1 = DAT_00ff615d;
      DAT_00ff6176 = DAT_00ff6176 | 2;
      DAT_00ff615d = DAT_00ff615d | 0x10;
      if (DAT_00ffe115 != '\x01') {
        DAT_00ff615d = bVar1 | 0x11;
      }
      do {
        while( true ) {
          while( true ) {
            while( true ) {
              FUN_00000e40();
              FUN_000180e6();
              if ((DAT_00ff6004 & 1) != 0) {
                FUN_00027f08();
                if (DAT_00ff615b == '\0') {
                  DAT_00ff615b = DAT_00ffe115;
                }
                DAT_00ff615b = DAT_00ff615b + -1;
                FUN_00017e64();
                DAT_00ff6019 = DAT_00ff6019 | 4;
                DAT_00ff601a = 0;
                DAT_00ff601b = 0;
                DAT_00ff601c = 8;
                do {
                  FUN_00000e40();
                  FUN_000180e6();
                  FUN_00002a52();
                  FUN_00002b1a();
                  DAT_00ff600a = DAT_00ff600a + -0x10;
                  Ram00c00004 = 0x40000010;
                  Ram00c00000 = DAT_00ff600a;
                  FUN_000194fe();
                } while ((char)DAT_00ff600a != '\0');
              }
              if ((DAT_00ff6004 & 2) != 0) {
                FUN_00027f08();
                DAT_00ff615b = DAT_00ff615b + '\x01';
                if (DAT_00ffe115 <= DAT_00ff615b) {
                  DAT_00ff615b = '\0';
                }
                FUN_00017e64();
                DAT_00ff6019 = DAT_00ff6019 | 4;
                DAT_00ff601a = 0;
                DAT_00ff601b = 0;
                DAT_00ff601c = 8;
                do {
                  FUN_00000e40();
                  FUN_000180e6();
                  FUN_00002a52();
                  FUN_00002b1a();
                  DAT_00ff600a = DAT_00ff600a + 0x10;
                  Ram00c00004 = 0x40000010;
                  Ram00c00000 = DAT_00ff600a;
                  FUN_000194fe();
                } while ((char)DAT_00ff600a != '\0');
              }
              if ((DAT_00ff6004 & 4) == 0) break;
              FUN_00027f08();
              bVar4 = DAT_00ff6177 == 0;
              DAT_00ff6177 = DAT_00ff6177 - 1;
              if (bVar4) {
                DAT_00ff6177 = 2;
              }
              FUN_00019670();
            }
            if ((DAT_00ff6004 & 8) == 0) break;
            FUN_00027f08();
            DAT_00ff6177 = DAT_00ff6177 + 1;
            if (2 < DAT_00ff6177) {
              DAT_00ff6177 = 0;
            }
            FUN_00019670();
          }
          if ((DAT_00ff6004 & 0x40) == 0) break;
          FUN_00027f18();
          if ((DAT_00ff6176 & 1) == 0) {
            FUN_00019e30();
            FUN_0001a454();
          }
          else {
            FUN_00019842();
          }
        }
      } while ((DAT_00ff6004 & 0x10) == 0);
      FUN_00027f18();
      DAT_00ff6176 = DAT_00ff6176 & 0xfd;
      DAT_00ff615d = DAT_00ff615d & 0xee;
      FUN_0001977c();
    }
  }
  FUN_00027f18();
  FUN_00000ef0();
  sVar2 = 0x12;
  puVar3 = &DAT_00028162;
  do {
    Ram00c00004 = *puVar3;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
  } while (sVar2 != -1);
  DAT_00ff6034 = 0;
  DAT_00ff6035 = 0;
  DAT_00ff6008 = 0;
  DAT_00ff600a = 0;
  DAT_00ff600c = 0;
  DAT_00ff600e = 0;
  FUN_00001098();
  FUN_00002d00();
  FUN_00002e84();
  FUN_00002ffc();
  DAT_00ff615d = 0;
  DAT_00ffe116 = 0;
  DAT_00ff6018 = DAT_00ff615a;
  DAT_00ff6019 = DAT_00ff6019 | 2;
  DAT_00ff601a = 0;
  DAT_00ff601b = 1;
  DAT_00ff601c = 0xf;
  DAT_00ff6036 = 0xff;
  return;
}

