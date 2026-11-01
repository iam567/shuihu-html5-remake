/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d3d2 */

void FUN_0000d3d2(void)

{
  ushort uVar1;
  undefined1 extraout_D1b;
  ushort uVar2;
  char *pcVar3;
  char *pcVar4;
  
  DAT_00ff610b = 0xff;
  uVar2 = 0;
  pcVar3 = &DAT_00ff7180;
  while (pcVar4 = pcVar3 + 1, *pcVar3 != -1) {
    uVar1 = FUN_0000d410();
    pcVar3 = pcVar4;
    if (uVar2 < uVar1) {
      uVar2 = uVar1;
      DAT_00ff610b = extraout_D1b;
    }
  }
  return;
}

