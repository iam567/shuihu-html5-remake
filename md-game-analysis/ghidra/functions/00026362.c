/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00026362 */

void FUN_00026362(void)

{
  byte bVar2;
  ushort uVar1;
  undefined2 *unaff_A2;
  
  if (DAT_00ff6086 != 0) {
    DAT_00ff6086 = DAT_00ff6086 + 1;
    if (DAT_00ff6086 == 0x40) {
      DAT_00ff6086 = 0;
      DAT_00ff603d = DAT_00ff603d | 2;
      DAT_00ffe050 = 0x3f;
    }
    else {
      *unaff_A2 = DAT_00ff60ae;
      unaff_A2[1] = DAT_00ff60b0;
      bVar2 = (byte)(DAT_00ff6086 - 2) >> 4;
      if (2 < bVar2) {
        bVar2 = 2;
      }
      unaff_A2[2] = (ushort)(byte)(bVar2 + 0x88);
      DAT_00ff6012 = DAT_00ff6012 + 1;
      if ((0x21 < DAT_00ff6086) && (DAT_00ff6086 < 0x32)) {
        uVar1 = (ushort)DAT_00ff6086;
        unaff_A2[3] = DAT_00ff60ae;
        unaff_A2[4] = DAT_00ff60b0 - ((uVar1 - 0x22) * 8 + 0x10);
        unaff_A2[5] = 0x8b;
        DAT_00ff6012 = DAT_00ff6012 + 1;
      }
    }
  }
  return;
}

