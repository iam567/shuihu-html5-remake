/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00014c12 */

void FUN_00014c12(void)

{
  ushort uVar1;
  
  if ((((DAT_00ff614f & 1) != 0) && (DAT_00ff6085 == '\0')) && ((DAT_00ff603d & 1) == 0)) {
    DAT_00ff614f = DAT_00ff614f & 0xfe;
    uVar1 = (ushort)DAT_00ff6150;
    FUN_00014c80();
    if (*(char *)((int)&DAT_00ffe780 + (int)(short)(uVar1 << 6)) != '\0') {
      DAT_00ff603d = DAT_00ff603d | 3;
      DAT_00ff6130 = &PTR_DAT_00014c7a;
    }
  }
  return;
}

