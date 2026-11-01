/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007842 */

void FUN_00007842(void)

{
  ushort uVar1;
  ushort uVar2;
  int unaff_A2;
  
  DAT_00ff6037 = DAT_00ff6037 & 0xfe;
  uVar1 = *(ushort *)(unaff_A2 + 2);
  uVar2 = *(ushort *)(unaff_A2 + 4);
  if (((uVar1 & 0x1f) == 0) && ((uVar2 & 0x1f) == 0)) {
    FUN_000079fa();
    if (0x4f < (byte)(&DAT_00ffd000)[(short)((uVar1 >> 5) + (uVar2 >> 5) * (ushort)DAT_00ffe106)]) {
      DAT_00ff6037 = DAT_00ff6037 | 1;
    }
  }
  return;
}

