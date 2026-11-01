/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00026ae8 */

short FUN_00026ae8(void)

{
  byte bVar1;
  short sVar2;
  uint unaff_D4;
  bool bVar3;
  
  bVar1 = DAT_00ff60ac;
  do {
    if ((bVar1 == DAT_00ff60ac) || ((short)unaff_D4 != 0)) {
      unaff_D4 = unaff_D4 / 10 & 0xffff;
      sVar2 = Seed_1028();
    }
    else {
      sVar2 = Seed_1028();
    }
    bVar3 = SBORROW1(DAT_00ff60ac,'\x01');
    DAT_00ff60ac = DAT_00ff60ac - 1;
  } while (DAT_00ff60ac != 0 && bVar3 == (short)((ushort)DAT_00ff60ac << 8) < 0);
  return sVar2 + -2;
}

