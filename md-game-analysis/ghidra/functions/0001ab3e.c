/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001ab3e */

void FUN_0001ab3e(void)

{
  DAT_00ff6036 = 0;
  FUN_00000ef0();
  DAT_00ff615a = DAT_00ff6018;
  DAT_00ff6018 = 0;
  DAT_00ffe116 = 0xff;
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
  Seed_e50();
  FUN_0001977c();
  Seed_1028();
  Seed_1060();
  DAT_00ff60b4 = 0x1001;
  DAT_00ff60b6 = 0x22;
  FUN_0001a6b0();
  Seed_e50();
  Seed_e50();
  DAT_00ff6190 = 9;
  DAT_00ff6192 = 2;
  FUN_0001c476();
  FUN_0001b34c();
  DAT_00ff6168 = 0xfffff;
  FUN_00018b8c();
  DAT_00ff6188 = 0;
  DAT_00ff615d = DAT_00ff615d | 0x80;
  DAT_00ff6189 = DAT_00ff6189 | 1;
  FUN_000180e6();
  FUN_00000e7c();
  do {
    while( true ) {
      while( true ) {
        FUN_00000e40();
        FUN_000180e6();
        if ((DAT_00ff6004 & 0xf) == 0) break;
        FUN_00027f08();
        DAT_00ff6188 = DAT_00ff6188 ^ 1;
      }
      if ((DAT_00ff6004 & 0x40) == 0) break;
      FUN_00027f18();
      if ((DAT_00ff6188 & 1) == 0) {
        FUN_0001ae42();
      }
      else {
        FUN_0001b0a8();
        FUN_0001a454();
      }
    }
  } while ((DAT_00ff6004 & 0x10) == 0);
  FUN_00027f18();
  FUN_00000ef0();
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
  DAT_00ff6189 = 0;
  DAT_00ffe116 = 0;
  DAT_00ff6018 = DAT_00ff615a;
  DAT_00ff6019 = DAT_00ff6019 | 2;
  DAT_00ff601a = 0;
  DAT_00ff601b = 1;
  DAT_00ff601c = 0xf;
  DAT_00ff601e._1_1_ = (byte)DAT_00ff601e | 1;
  DAT_00ff6036 = 0xff;
  return;
}

