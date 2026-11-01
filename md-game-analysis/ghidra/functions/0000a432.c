/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000a432 */

void FUN_0000a432(void)

{
  ushort uVar1;
  
  if (DAT_00ff609d != '\0') {
    if (DAT_00ff6094 == DAT_00ff6098) {
      DAT_00ff609d = '\0';
    }
    else if (DAT_00ff6098 < DAT_00ff6094) {
      uVar1 = DAT_00ff6142 / 10;
      if (DAT_00ff6142 % 10 != 0) {
        uVar1 = uVar1 + 1;
      }
      DAT_00ff6094 = DAT_00ff6094 - uVar1;
      if ((short)DAT_00ff6094 < (short)DAT_00ff6098) {
        DAT_00ff6094 = DAT_00ff6098;
      }
    }
    else {
      uVar1 = DAT_00ff6152 / 0x30;
      if (DAT_00ff6152 % 0x30 != 0) {
        uVar1 = uVar1 + 1;
      }
      DAT_00ff6094 = uVar1 + DAT_00ff6094;
      if (DAT_00ff6098 <= DAT_00ff6094) {
        DAT_00ff6094 = DAT_00ff6098;
      }
    }
  }
  return;
}

