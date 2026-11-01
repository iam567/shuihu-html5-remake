/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00016486 */

void FUN_00016486(void)

{
  short sVar1;
  undefined2 *unaff_A2;
  char *pcVar2;
  
  if (DAT_00ff614a != '\0') {
    pcVar2 = &DAT_00ff5100;
    sVar1 = 0x2f;
    do {
      if (*pcVar2 != '\0') {
        *unaff_A2 = *(undefined2 *)(pcVar2 + 2);
        unaff_A2[1] = *(undefined2 *)(pcVar2 + 4);
        *pcVar2 = *pcVar2 + -1;
        unaff_A2[2] = (ushort)(byte)(0x4c - *pcVar2);
        DAT_00ff6012 = DAT_00ff6012 + 1;
        unaff_A2 = unaff_A2 + 3;
      }
      pcVar2 = pcVar2 + 6;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
  }
  return;
}

