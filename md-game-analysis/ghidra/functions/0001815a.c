/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001815a */

void FUN_0001815a(void)

{
  undefined2 uVar1;
  undefined2 *unaff_A2;
  
  if ((DAT_00ff615d & 1) != 0) {
    *unaff_A2 = 0xd0;
    unaff_A2[1] = 0x90;
    uVar1 = 0x48;
    if (7 < ((byte)DAT_00ff6010 & 0xf)) {
      uVar1 = 0x51;
    }
    unaff_A2[2] = uVar1;
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

