/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000cf52 */

void FUN_0000cf52(void)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int unaff_A2;
  
  bVar1 = ('\n' - (char)(((uint)*(ushort *)(unaff_A2 + 0x12) * 10) /
                        (uint)*(ushort *)(unaff_A2 + 0x1e))) * '\b';
  if (*(char *)(unaff_A2 + 0xd) == '\0') {
    bVar1 = 0;
  }
  bVar2 = *(char *)(unaff_A2 + 0xc) << 4;
  uVar3 = 0xff00ffff;
  DAT_00ff6109 = 2;
  if (bVar1 < bVar2) {
    uVar3 = 0xffffff;
    DAT_00ff6109 = 1;
    bVar1 = bVar2;
  }
  if (bVar1 < *(byte *)(unaff_A2 + 0xe)) {
    uVar3 = 0xffff00ff;
    DAT_00ff6109 = 3;
    bVar1 = *(byte *)(unaff_A2 + 0xe);
  }
  if (bVar1 < *(byte *)(unaff_A2 + 0xf)) {
    uVar3 = 0xffffff00;
    DAT_00ff6109 = 4;
  }
  *(uint *)(unaff_A2 + 0xc) = uVar3 & *(uint *)(unaff_A2 + 0xc);
  return;
}

