/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00019e30 */

void FUN_00019e30(void)

{
  FUN_0001a08e();
  if (DAT_00ff6180 != '\0') {
    DAT_00ff617e = 1;
    DAT_00ff617c = 0x170;
    DAT_00ff615d = DAT_00ff615d & 0xfe;
    DAT_00ff615d = DAT_00ff615d | 0x60;
    DAT_00ff617a = '\0';
    DAT_00ff617f = '\0';
    DAT_00ff6178 = 0xe8;
    FUN_00019fe6();
    FUN_0001a068();
    do {
      while( true ) {
        while( true ) {
          while( true ) {
            FUN_00000e40();
            FUN_000180e6();
            if ((DAT_00ff6004 & 1) == 0) break;
            if (DAT_00ff617a != '\0') {
              FUN_00027f08();
              DAT_00ff617a = DAT_00ff617a + -1;
              if (DAT_00ff6178 == 0xe8) {
                DAT_00ff617f = DAT_00ff617f + -1;
                FUN_00019fe6();
                FUN_0001a068();
              }
              else {
                DAT_00ff6178 = DAT_00ff6178 + -0x10;
                FUN_0001a068();
              }
            }
          }
          if ((DAT_00ff6004 & 2) == 0) break;
          if ((char)(DAT_00ff6180 + -1) != DAT_00ff617a) {
            FUN_00027f08();
            DAT_00ff617a = DAT_00ff617a + '\x01';
            if (DAT_00ff6178 == 0x128) {
              DAT_00ff617f = DAT_00ff617f + '\x01';
              FUN_00019fe6();
              FUN_0001a068();
            }
            else {
              DAT_00ff6178 = DAT_00ff6178 + 0x10;
              FUN_0001a068();
            }
          }
        }
        if ((DAT_00ff6004 & 0x40) == 0) break;
        FUN_00027fa8();
        FUN_0001a370();
        if ((DAT_00ff6037 & 1) != 0) {
          FUN_00027f18();
          FUN_0001a3ee();
          FUN_00019670();
        }
      }
    } while ((DAT_00ff6004 & 0x10) == 0);
    FUN_00027f18();
    DAT_00ff615d = DAT_00ff615d & 0x9f | 1;
    DAT_00ff617e = 2;
    DAT_00ff617c = 0x140;
    FUN_0001977c();
    Seed_1060();
  }
  return;
}

