/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000048c */

void FUN_0000048c(void)

{
  byte bVar1;
  byte bVar2;
  byte *unaff_A5;
  byte *unaff_A6;
  
  *unaff_A6 = 0;
  bVar1 = *unaff_A6;
  *unaff_A6 = 0x40;
  bVar2 = ~(*unaff_A6 & 0x3f | (bVar1 & 0x30) << 2);
  bVar1 = *unaff_A5;
  *unaff_A5 = bVar2;
  unaff_A5[1] = bVar2 & (bVar2 ^ bVar1);
  return;
}

