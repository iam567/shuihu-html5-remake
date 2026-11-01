/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00000478 */

void FUN_00000478(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  FUN_0000048c();
  bVar3 = DAT_00ff6003;
  UNK_00a10005 = 0;
  bVar1 = UNK_00a10005;
  UNK_00a10005 = 0x40;
  bVar2 = UNK_00a10005;
  DAT_00ff6003 = ~(bVar2 & 0x3f | (bVar1 & 0x30) << 2);
  DAT_00ff6004 = DAT_00ff6003 & (DAT_00ff6003 ^ bVar3);
  return;
}

