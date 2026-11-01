/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e7720 */

undefined1 FUN_001e7720(void)

{
  byte bVar1;
  undefined1 uVar2;
  byte unaff_D6b;
  byte *pbVar3;
  byte *pbVar4;
  undefined4 *unaff_A5;
  
  uVar2 = 0;
  if (*(char *)((int)unaff_A5 + 5) != '\0' || *(char *)(unaff_A5 + 1) != '\0') {
    pbVar4 = (byte *)*unaff_A5;
    if (*(char *)(unaff_A5 + 1) != '\0') {
      *(byte *)((int)unaff_A5 + 5) = *(byte *)((int)unaff_A5 + 5) | 0x80;
      pbVar4 = *(byte **)(&DAT_001d877a + (short)((*(byte *)(unaff_A5 + 1) & 0x7f) * 4));
      *(undefined1 *)(unaff_A5 + 1) = 0;
      *(undefined1 *)((int)unaff_A5 + 6) = 0;
    }
    while( true ) {
      pbVar3 = pbVar4 + 1;
      bVar1 = *pbVar4;
      if (-1 < (char)bVar1) break;
      if ((bVar1 & 0x7f) == 0) {
        *(undefined1 *)((int)unaff_A5 + 5) = 0;
        uVar2 = FUN_001e77d8();
        return uVar2;
      }
      (**(code **)((int)&PTR_LAB_001e7784 + (int)(short)(((bVar1 & 0x7f) - 1) * 4)))();
      pbVar4 = pbVar3;
    }
    if (bVar1 == 0x7f) {
      uVar2 = FUN_001e77d8();
      pbVar4 = pbVar3;
    }
    else {
      DAT_00c00011 = unaff_D6b | bVar1;
      pbVar4 = pbVar4 + 2;
      DAT_00c00011 = *pbVar3;
      uVar2 = FUN_001e77b8();
    }
    *unaff_A5 = pbVar4;
  }
  return uVar2;
}

