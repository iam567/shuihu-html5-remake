/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000a138 */

void FUN_0000a138(void)

{
  ushort uVar1;
  
  if (DAT_00ff609c != '\0') {
    if (DAT_00ff608e == DAT_00ff6092) {
      DAT_00ff609c = '\0';
    }
    else if (DAT_00ff6092 < DAT_00ff608e) {
      uVar1 = DAT_00ff6142 / 10;
      if (DAT_00ff6142 % 10 != 0) {
        uVar1 = uVar1 + 1;
      }
      DAT_00ff608e = DAT_00ff608e - uVar1;
      if ((short)DAT_00ff608e < (short)DAT_00ff6092) {
        DAT_00ff608e = DAT_00ff6092;
      }
    }
    else {
      uVar1 = DAT_00ff6152 / 0x30;
      if (DAT_00ff6152 % 0x30 != 0) {
        uVar1 = uVar1 + 1;
      }
      DAT_00ff608e = uVar1 + DAT_00ff608e;
      if ((short)DAT_00ff6092 < (short)DAT_00ff608e) {
        DAT_00ff608e = DAT_00ff6092;
      }
    }
  }
  return;
}

