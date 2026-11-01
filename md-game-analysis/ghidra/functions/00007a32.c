/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007a32 */

undefined8 FUN_00007a32(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar1;
  ushort uVar2;
  int unaff_A2;
  
  if (((*(byte *)(unaff_A2 + 6) < 4) &&
      (DAT_00ff6037 = DAT_00ff6037 & 0xfe, (*(ushort *)(unaff_A2 + 2) & 0x1f) == 0)) &&
     ((*(ushort *)(unaff_A2 + 4) & 0x1f) == 0)) {
    uVar1 = *(ushort *)(unaff_A2 + 2) >> 5;
    uVar2 = *(ushort *)(unaff_A2 + 4) >> 5;
    FUN_00007ac2();
    if ((uVar1 == DAT_00ffe002 >> 5) ||
       (((DAT_00ffe002 & 0x1f) != 0 && (uVar1 == (ushort)((DAT_00ffe002 >> 5) + 1))))) {
      if ((uVar2 == DAT_00ffe004 >> 5) ||
         (((DAT_00ffe004 & 0x1f) != 0 && (uVar2 == (ushort)((DAT_00ffe004 >> 5) + 1))))) {
        DAT_00ff6037 = DAT_00ff6037 | 1;
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}

