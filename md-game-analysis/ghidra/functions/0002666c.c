/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0002666c */

void FUN_0002666c(void)

{
  if ((DAT_00ff603d & 1) == 0) {
    DAT_00ff6036 = 0;
    FUN_00000ef0();
    DAT_00ff615a = DAT_00ff6018;
    DAT_00ff6018 = 0;
    FUN_00001098();
    FUN_000010c8();
    Ram00c00004 = 0x74000003;
    Ram00c00000 = 0;
    Ram00c00004 = 0x74020003;
    Ram00c00000 = 0;
    Ram00c00004 = 0x40000010;
    Ram00c00000 = 0;
    Ram00c00004 = 0x40020010;
    Ram00c00000 = 0;
    FUN_000010e0();
    FUN_00000e40();
    Seed_e50();
    FUN_0001977c();
    Seed_1028();
    Seed_1060();
    DAT_00ff60b4 = 0x1001;
    DAT_00ff60b6 = 0x22;
    FUN_00026972();
    DAT_00ff605c._1_1_ = 0xb;
    FUN_00026c78();
    DAT_00ff605c._1_1_ = 0x15;
    FUN_00026c78();
    DAT_00ff6174 = '\0';
    DAT_00ff6189 = DAT_00ff6189 | 0x20;
    FUN_00000e7c();
    do {
      while( true ) {
        while( true ) {
          while( true ) {
            FUN_00000e40();
            FUN_000180e6();
            if ((DAT_00ff6004 & 0x40) == 0) break;
            FUN_00027f18();
            DAT_00ff605c._1_1_ = 0xb;
            if (DAT_00ff6174 != '\0') {
              DAT_00ff605c._1_1_ = 0x15;
            }
            FUN_00026c10();
            FUN_00026ba2();
          }
          if ((DAT_00ff6004 & 1) == 0) break;
          FUN_00027f08();
          DAT_00ff6174 = '\0';
        }
        if ((DAT_00ff6004 & 2) == 0) break;
        FUN_00027f08();
        DAT_00ff6174 = '\x01';
      }
    } while ((DAT_00ff6004 & 0x10) == 0);
    FUN_00027f18();
    FUN_00000ef0();
    DAT_00ff619b = 0;
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
    DAT_00ff6189 = 0;
    DAT_00ff601e._1_1_ = (byte)DAT_00ff601e | 1;
    DAT_00ff6036 = 0xff;
  }
  return;
}

