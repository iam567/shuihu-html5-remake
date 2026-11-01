/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000789e */

void FUN_0000789e(void)

{
  undefined2 uVar1;
  int unaff_A2;
  
  if ((DAT_00ff6010 & 0x1f) == 0) {
    if (((*(ushort *)(unaff_A2 + 2) & 0x1f) == 0) && ((*(ushort *)(unaff_A2 + 4) & 0x1f) == 0)) {
      uVar1 = DAT_00c00008;
      *(byte *)(unaff_A2 + 6) = (byte)uVar1 & 3;
    }
    else {
      FUN_000078ec();
    }
    FUN_00007934();
  }
  return;
}

