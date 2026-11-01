/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00016bfa */

void FUN_00016bfa(void)

{
  short sVar1;
  char cVar2;
  ushort *unaff_A2;
  ushort *puVar3;
  
  if (DAT_00ff6154 != '\0') {
    cVar2 = '\0';
    puVar3 = &DAT_00ff6330;
    sVar1 = 0x24;
    do {
      if (*puVar3 != 0) {
        cVar2 = cVar2 + '\x01';
        *unaff_A2 = puVar3[1];
        unaff_A2[1] = puVar3[2];
        *puVar3 = *puVar3 - 1;
        unaff_A2[2] = 0x50 - (*puVar3 >> 3);
        unaff_A2 = unaff_A2 + 3;
        DAT_00ff6012 = DAT_00ff6012 + 1;
      }
      puVar3 = puVar3 + 3;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    if ((cVar2 == '\0') && (DAT_00ff6312 == '\0')) {
      DAT_00ff6154 = '\0';
      DAT_00ff6036 = 0xff;
    }
  }
  return;
}

