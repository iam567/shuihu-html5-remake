/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00018a46 */

void FUN_00018a46(void)

{
  short sVar1;
  ushort uVar2;
  undefined2 *unaff_A2;
  char *pcVar3;
  undefined *puVar4;
  
  if ((DAT_00ff6189 & 1) != 0) {
    puVar4 = &DAT_00002330;
    pcVar3 = &DAT_00ff8000;
    sVar1 = 0x13;
    do {
      if (*pcVar3 != '\0') {
        *unaff_A2 = *(undefined2 *)(pcVar3 + 2);
        unaff_A2[1] = *(undefined2 *)(pcVar3 + 4);
        uVar2 = *(ushort *)(puVar4 + (short)((ushort)(byte)pcVar3[1] << 1));
        if (pcVar3[0x1d] != '\0') {
          uVar2 = uVar2 | 0x6000;
        }
        unaff_A2[2] = uVar2;
        DAT_00ff6012 = DAT_00ff6012 + 1;
        unaff_A2 = unaff_A2 + 3;
      }
      puVar4 = puVar4 + 0x24;
      pcVar3 = pcVar3 + 0x40;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
  }
  return;
}

