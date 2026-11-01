/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000cdd0 */

void FUN_0000cdd0(void)

{
  byte bVar1;
  undefined1 extraout_D1b;
  byte bVar2;
  char *pcVar3;
  char *pcVar4;
  
  DAT_00ff6108 = 0xff;
  bVar2 = 0;
  pcVar3 = &DAT_00ff7180;
  while (pcVar4 = pcVar3 + 1, *pcVar3 != -1) {
    bVar1 = FUN_0000ce0e();
    pcVar3 = pcVar4;
    if (bVar2 <= bVar1) {
      bVar2 = bVar1;
      DAT_00ff6108 = extraout_D1b;
    }
  }
  return;
}

