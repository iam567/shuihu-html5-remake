/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000c438 */

void FUN_0000c438(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  if (DAT_00ff6103 != '\0') {
    DAT_00ff6103 = DAT_00ff6103 + -1;
    Ram00c00004 = 0x8134;
    Ram00c00004 = 0xc0000000;
    sVar1 = 0x3f;
    if (DAT_00ff6103 == '\0') {
      puVar2 = &DAT_00ffef80;
      do {
        Ram00c00000 = *puVar2;
        sVar1 = sVar1 + -1;
        puVar2 = puVar2 + 1;
      } while (sVar1 != -1);
    }
    else {
      do {
        Ram00c00000 = 0xeee;
        sVar1 = sVar1 + -1;
      } while (sVar1 != -1);
    }
    Ram00c00004 = 0x8174;
  }
  return;
}

