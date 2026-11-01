/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000b3ec */

short FUN_0000b3ec(void)

{
  short sVar1;
  uint unaff_D4;
  bool bVar2;
  
  do {
    if ((short)unaff_D4 == 0) {
      sVar1 = FUN_00006f50();
    }
    else {
      unaff_D4 = unaff_D4 / 10 & 0xffff;
      sVar1 = FUN_00006f50();
    }
    bVar2 = SBORROW1(DAT_00ff60ac,'\x01');
    DAT_00ff60ac = DAT_00ff60ac - 1;
  } while (DAT_00ff60ac != 0 && bVar2 == (short)((ushort)DAT_00ff60ac << 8) < 0);
  return sVar1 + -1;
}

