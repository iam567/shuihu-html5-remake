/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000092c2 */

void FUN_000092c2(void)

{
  byte bVar1;
  ushort uVar2;
  int unaff_A2;
  
  uVar2 = 0x30;
  while( true ) {
    if (*(byte *)(unaff_A2 + (short)uVar2) == 0xff) {
      return;
    }
    if (*(char *)((int)&DAT_00ffe780 + (int)(short)((ushort)*(byte *)(unaff_A2 + (short)uVar2) << 6)
                 ) != '\0') break;
    bVar1 = (char)uVar2 + 1;
    uVar2 = (ushort)bVar1;
    if (bVar1 == 0x10) {
      return;
    }
  }
  return;
}

