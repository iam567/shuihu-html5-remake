/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000146a4 */

void FUN_000146a4(void)

{
  short sVar1;
  short sVar2;
  short *unaff_A2;
  
  if (DAT_00ff6148 != '\0') {
    if (DAT_00ff6148 == '\x01') {
      FUN_000147a4();
    }
    sVar1 = DAT_00ff6144 - DAT_00ff6014;
    sVar2 = sVar1 + 0x84;
    if ((DAT_00ff6142 < 100) && (sVar2 = sVar1 + 0x80, DAT_00ff6142 < 10)) {
      sVar2 = sVar1 + 0x7c;
    }
    *unaff_A2 = sVar2;
    unaff_A2[1] = *(short *)((int)&PTR_DAT_00014744 +
                            (int)(short)((ushort)((byte)(DAT_00ff6148 - 1U) >> 1) << 1)) +
                  ((DAT_00ff6146 + 0x80) - DAT_00ff6016);
    unaff_A2[2] = 0x47;
    DAT_00ff6012 = DAT_00ff6012 + 1;
    DAT_00ff6148 = DAT_00ff6148 + '\x01';
    if (DAT_00ff6148 == '`') {
      DAT_00ff6148 = '\0';
    }
  }
  return;
}

