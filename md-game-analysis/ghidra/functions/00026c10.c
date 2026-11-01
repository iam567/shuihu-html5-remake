/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00026c10 */

undefined8 FUN_00026c10(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  int unaff_A6;
  
  *(undefined1 *)(unaff_A6 + 1) = 6;
  *(undefined1 *)(unaff_A6 + 3) = 9;
  *(undefined1 *)(unaff_A6 + 5) = 1;
  *(undefined1 *)(unaff_A6 + 7) = 8;
  pbVar4 = (byte *)(unaff_A6 + 0x11);
  iVar2 = 0;
  sVar1 = 0x7f7;
  pbVar3 = &DAT_00ffe000;
  if (unaff_A6 == 0x200000) {
    sVar1 = 0xff7;
  }
  do {
    iVar2 = (uint)*pbVar3 + iVar2;
    *pbVar4 = *pbVar3;
    pbVar4 = pbVar4 + 2;
    sVar1 = sVar1 + -1;
    pbVar3 = pbVar3 + 1;
  } while (sVar1 != -1);
  *(char *)(unaff_A6 + 9) = (char)iVar2;
  *(char *)(unaff_A6 + 0xb) = (char)((uint)iVar2 >> 8);
  *(char *)(unaff_A6 + 0xd) = (char)((uint)iVar2 >> 0x10);
  *(char *)(unaff_A6 + 0xf) = (char)((uint)iVar2 >> 0x18);
  return CONCAT44(in_D0,in_D1);
}

