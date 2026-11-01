/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00008d48 */

void FUN_00008d48(void)

{
  short sVar1;
  short unaff_D3w;
  char *pcVar2;
  
  sVar1 = 0xb;
  pcVar2 = (char *)&DAT_00ffe780;
  do {
    if (*pcVar2 != '\0') {
      sVar1 = FUN_00006902();
      *(undefined1 *)((int)&DAT_00ffb000 + (int)unaff_D3w) = 0x7f;
    }
    pcVar2 = pcVar2 + 0x40;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}

