/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001a4be */

void FUN_0001a4be(void)

{
  undefined2 uVar1;
  undefined2 *unaff_A2;
  
  if ((DAT_00ff615d & 0x40) != 0) {
    if (DAT_00ff617f != '\0') {
      *unaff_A2 = 0x160;
      uVar1 = 0xd9;
      if (7 < ((byte)DAT_00ff6010 & 0xf)) {
        uVar1 = 0xdb;
      }
      unaff_A2[1] = uVar1;
      unaff_A2[2] = 0x5e;
      unaff_A2 = unaff_A2 + 3;
      DAT_00ff6012 = DAT_00ff6012 + 1;
    }
    if ((5 < DAT_00ff6180) && ((byte)(DAT_00ff6180 - 5) != DAT_00ff617f)) {
      *unaff_A2 = 0x160;
      uVar1 = 0x136;
      if (7 < ((byte)DAT_00ff6010 & 0xf)) {
        uVar1 = 0x138;
      }
      unaff_A2[1] = uVar1;
      unaff_A2[2] = 0x5f;
      DAT_00ff6012 = DAT_00ff6012 + 1;
    }
  }
  return;
}

