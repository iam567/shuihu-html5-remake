/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001c4d2 */

void FUN_0001c4d2(void)

{
  char extraout_D1b;
  ushort uVar1;
  uint unaff_D5;
  int unaff_D6;
  
  do {
    unaff_D5 = unaff_D5 / 10 & 0xffff;
    FUN_0001c524();
    DAT_00ff6190 = DAT_00ff6190 + -1;
  } while (unaff_D5 != 0);
  if ((unaff_D6 != 0) && ((char)(extraout_D1b + '\x01') < '\x04')) {
    uVar1 = (ushort)(byte)(3 - (extraout_D1b + '\x01'));
    do {
      FUN_0001c524();
      DAT_00ff6190 = DAT_00ff6190 + -1;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0xffff);
  }
  return;
}

