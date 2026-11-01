/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003a82 */

void FUN_00003a82(void)

{
  if (DAT_00ff603a != '\0') {
    DAT_00ff603a = '\0';
    Ram00c00004 = 0x74020003;
    Ram00c00000 = DAT_00ff600c;
    Ram00c00004 = 0x40020010;
    Ram00c00000 = DAT_00ff600e;
    Ram00c00004 = 0x74000003;
    Ram00c00000 = DAT_00ff6008;
    Ram00c00004 = 0x40000010;
    Ram00c00000 = DAT_00ff600a;
  }
  return;
}

