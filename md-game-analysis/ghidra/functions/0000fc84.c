/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000fc84 */

void FUN_0000fc84(void)

{
  if ((DAT_00ff612a != '\0') && ((DAT_00ff6004 & 0x40) != 0)) {
    DAT_00ff612a = '\0';
    DAT_00ff6140 = 0;
  }
  return;
}

