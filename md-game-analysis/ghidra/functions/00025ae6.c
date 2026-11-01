/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00025ae6 */

void FUN_00025ae6(void)

{
  undefined2 uVar1;
  undefined4 *unaff_A2;
  
  if (DAT_00ff619e != '\0') {
    *unaff_A2 = DAT_00ff61a0;
    uVar1 = 0x68;
    if (7 < ((byte)DAT_00ff6010 & 0xf)) {
      uVar1 = 0x69;
    }
    *(undefined2 *)(unaff_A2 + 1) = uVar1;
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

