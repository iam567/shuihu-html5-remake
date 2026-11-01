/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000194fe */

void FUN_000194fe(void)

{
  if ((char)DAT_00ff600a == 'p') {
    if (DAT_00ff6177 == '\0') {
      FUN_0000b7fe();
      FUN_0000b7fe();
    }
    else if (DAT_00ff6177 == '\x01') {
      FUN_0000b7fe();
      FUN_0000b7fe();
    }
    else {
      FUN_0000b7fe();
      FUN_0000b7fe();
    }
  }
  else if ((char)DAT_00ff600a == -0x80) {
    DAT_00ff6019 = DAT_00ff6019 | 8;
    DAT_00ff601a = 0;
    if (DAT_00ff6177 == '\0') {
      FUN_0000b7fe();
      FUN_0000b7fe();
    }
    else if (DAT_00ff6177 == '\x01') {
      FUN_0000b7fe();
      FUN_0000b7fe();
    }
    else {
      FUN_0000b7fe();
      FUN_0000b7fe();
    }
  }
  return;
}

