/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000fca8 */

void FUN_0000fca8(void)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  
  if (((DAT_00ff6030 == '\0') && ((DAT_00ff603d & 1) != 0)) &&
     (DAT_00ff6036 = 0, puVar2 = DAT_00ff6130, (DAT_00ff603d & 2) != 0)) {
    while( true ) {
      puVar3 = puVar2 + 1;
      uVar1 = *puVar2;
      if (uVar1 == 0xffff) break;
      puVar2 = puVar3;
      if (uVar1 < 0x1000) {
        (**(code **)(&DAT_0000fd46 + (short)(uVar1 << 2)))();
        if ((DAT_00ff6157 & 1) == 0) {
          return;
        }
        DAT_00ff6157 = DAT_00ff6157 & 0xfe;
      }
    }
    DAT_00ff603d = DAT_00ff603d & 0xfe;
    DAT_00ff6036 = 1;
    DAT_00ffe10e = DAT_00ffe1f6;
    DAT_00ffe10d = 2;
    if (DAT_00ffe116 != '\0') {
      DAT_00ffe10e = 4;
    }
  }
  return;
}

