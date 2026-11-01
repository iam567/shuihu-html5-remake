/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00014aea */

void FUN_00014aea(void)

{
  if (DAT_00ff614c != '\0') {
    if (DAT_00ff614c == '\x01') {
      FUN_00006f50();
    }
    else if (DAT_00ff614c == '\t') {
      DAT_00ff6103 = 2;
      FUN_00006f50();
    }
    DAT_00ff614c = DAT_00ff614c + '\x01';
    if (DAT_00ff614c == ')') {
      DAT_00ff614c = '\0';
      DAT_00ff6120 = 0xff;
      DAT_00ff603d = DAT_00ff603d | 2;
      FUN_00001098();
    }
  }
  return;
}

