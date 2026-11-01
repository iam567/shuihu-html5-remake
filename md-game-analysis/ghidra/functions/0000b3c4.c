/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000b3c4 */

void FUN_0000b3c4(void)

{
  if ((DAT_00ff6004 & 0x10) != 0) {
    FUN_00006912();
    FUN_00001098();
    DAT_00ff605f = 0;
    DAT_00ff6085 = 1;
  }
  return;
}

