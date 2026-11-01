/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001782a */

void FUN_0001782a(void)

{
  short sVar1;
  char cVar2;
  undefined2 *puVar3;
  
  DAT_00ff6036 = 0;
  FUN_00000ef0();
  DAT_00ff615a = DAT_00ff6018;
  DAT_00ff6018 = 0;
  DAT_00ffe116 = 0xff;
  FUN_00001098();
  FUN_000010ac();
  FUN_000010c8();
  if (DAT_00ffe115 != '\x01') {
    DAT_00ff615d = 1;
  }
  sVar1 = 0x12;
  puVar3 = &DAT_00017608;
  do {
    Ram00c00004 = *puVar3;
    sVar1 = sVar1 + -1;
    puVar3 = puVar3 + 1;
  } while (sVar1 != -1);
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
  Seed_1028();
  Seed_1060();
  FUN_000192cc();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_0000b7fe();
  FUN_00000e7c();
  DAT_00ff615b = '\0';
  do {
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
        while( true ) {
          while( true ) {
            while( true ) {
              FUN_00000e40();
              FUN_000180e6();
              FUN_00002a52();
              FUN_00002b1a();
              DAT_00ff600a = DAT_00ff600a + -0x10;
              Ram00c00004 = 0x40000010;
              Ram00c00000 = DAT_00ff600a;
              cVar2 = (char)DAT_00ff600a;
              if (cVar2 != 'p') break;
              FUN_0000b7fe();
              FUN_0000b7fe();
              FUN_0000b7fe();
            }
            if (cVar2 != -0x80) break;
            DAT_00ff6019 = DAT_00ff6019 | 8;
            DAT_00ff601a = 0;
            FUN_0000b7fe();
            FUN_0000b7fe();
            FUN_0000b7fe();
          }
          if (cVar2 != '`') break;
          FUN_0000b7fe();
          FUN_0000b7fe();
          FUN_0000b7fe();
        }
      } while (cVar2 != '\0');
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
        while( true ) {
          while( true ) {
            while( true ) {
              FUN_00000e40();
              FUN_000180e6();
              FUN_00002a52();
              FUN_00002b1a();
              DAT_00ff600a = DAT_00ff600a + 0x10;
              Ram00c00004 = 0x40000010;
              Ram00c00000 = DAT_00ff600a;
              cVar2 = (char)DAT_00ff600a;
              if (cVar2 != 'p') break;
              FUN_0000b7fe();
              FUN_0000b7fe();
              FUN_0000b7fe();
            }
            if (cVar2 != -0x80) break;
            DAT_00ff6019 = DAT_00ff6019 | 8;
            DAT_00ff601a = 0;
            FUN_0000b7fe();
            FUN_0000b7fe();
            FUN_0000b7fe();
          }
          if (cVar2 != -0x70) break;
          FUN_0000b7fe();
          FUN_0000b7fe();
          FUN_0000b7fe();
        }
      } while (cVar2 != '\0');
    }
  } while ((DAT_00ff6004 & 0x10) == 0);
  FUN_00027f18();
  FUN_00000ef0();
  sVar1 = 0x12;
  puVar3 = &DAT_00028162;
  do {
    Ram00c00004 = *puVar3;
    sVar1 = sVar1 + -1;
    puVar3 = puVar3 + 1;
  } while (sVar1 != -1);
  DAT_00ff6034 = 0;
  DAT_00ff6035 = 0;
  DAT_00ff6008 = 0;
  DAT_00ff600a = 0;
  DAT_00ff600c = 0;
  DAT_00ff600e = 0;
  FUN_00001098();
  FUN_000010ac();
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

