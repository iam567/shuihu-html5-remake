/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00025270 */

void FUN_00025270(void)

{
  bool bVar1;
  
  if (DAT_00ff619b != '\0') {
    if ((DAT_00ff6004 & 1) == 0) {
      if ((DAT_00ff6004 & 2) == 0) {
        if ((DAT_00ff6004 & 0x40) == 0) {
          if ((DAT_00ff6004 & 0x10) == 0) {
            return;
          }
          FUN_00027f18();
        }
        else {
          FUN_00027f18();
          if (DAT_00ff619a == 0) {
            FUN_00018e2c();
            DAT_00ff619b = 0;
            return;
          }
          if (DAT_00ff619a == 1) {
            FUN_0001782a();
            DAT_00ff619b = 0;
            return;
          }
          if (DAT_00ff619a != 2) {
            FUN_00026ce6();
            return;
          }
          FUN_0002666c();
        }
        DAT_00ff619b = '\0';
        DAT_00ff6036 = 0xff;
        FUN_00001098();
      }
      else {
        FUN_00027f08();
        FUN_000254a0();
        DAT_00ff619a = DAT_00ff619a + 1;
        if (3 < DAT_00ff619a) {
          DAT_00ff619a = 0;
        }
        FUN_00025472();
      }
    }
    else {
      FUN_00027f08();
      FUN_000254a0();
      bVar1 = DAT_00ff619a == 0;
      DAT_00ff619a = DAT_00ff619a - 1;
      if (bVar1) {
        DAT_00ff619a = 3;
      }
      FUN_00025472();
    }
  }
  return;
}

