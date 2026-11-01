/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d410 */

ushort FUN_0000d410(void)

{
  ushort uVar1;
  short unaff_D3w;
  int unaff_A4;
  
  if (DAT_00ff610c == '\x04') {
    uVar1 = *(ushort *)(unaff_A4 + 0x1e + (int)unaff_D3w);
  }
  else if (DAT_00ff610c == '\x03') {
    uVar1 = (ushort)*(byte *)((int)&PTR_DAT_0000d46e +
                             (int)(short)(ushort)(byte)(*(char *)(unaff_A4 + 0x24 + (int)unaff_D3w)
                                                       - 1));
  }
  else if (DAT_00ff610c == '\x05') {
    uVar1 = (ushort)(byte)(*(char *)(unaff_A4 + 0x15 + (int)unaff_D3w) +
                          *(char *)(unaff_A4 + 0x14 + (int)unaff_D3w));
  }
  else {
    uVar1 = (ushort)(byte)(*(char *)(unaff_A4 + 0x17 + (int)unaff_D3w) +
                          *(char *)(unaff_A4 + 0x16 + (int)unaff_D3w));
  }
  return uVar1;
}

