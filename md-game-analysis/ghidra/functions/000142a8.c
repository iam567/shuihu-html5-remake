/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000142a8 */

void FUN_000142a8(void)

{
  short sVar1;
  short unaff_D3w;
  int extraout_A1;
  char *pcVar2;
  
  FUN_00006912();
  pcVar2 = (char *)&DAT_00ffe780;
  sVar1 = 0x1d;
  do {
    if (*pcVar2 != '\0') {
      sVar1 = FUN_00006902();
      *(undefined1 *)(extraout_A1 + unaff_D3w) = 0x7f;
    }
    pcVar2 = pcVar2 + 0x40;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}

