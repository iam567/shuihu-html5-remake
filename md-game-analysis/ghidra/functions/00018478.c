/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00018478 */

void FUN_00018478(void)

{
  int unaff_A2;
  
  DAT_00ff6161 = *(undefined1 *)(unaff_A2 + 1);
  DAT_00ff6162 = *(undefined1 *)(unaff_A2 + 6);
  if (*(char *)(unaff_A2 + 6) != -2) {
    if (DAT_00ffe006 == '\0') {
      *(undefined1 *)(unaff_A2 + 1) = 4;
      *(undefined1 *)(unaff_A2 + 6) = 0xff;
    }
    else if (DAT_00ffe006 == '\x01') {
      *(undefined1 *)(unaff_A2 + 1) = 0;
      *(undefined1 *)(unaff_A2 + 6) = 0xff;
    }
    else if (DAT_00ffe006 == '\x02') {
      *(undefined1 *)(unaff_A2 + 1) = 0xc;
      *(undefined1 *)(unaff_A2 + 6) = 0xff;
    }
    else {
      *(undefined1 *)(unaff_A2 + 1) = 8;
      *(undefined1 *)(unaff_A2 + 6) = 0xff;
    }
  }
  return;
}

