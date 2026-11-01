/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007934 */

void FUN_00007934(void)

{
  int unaff_A2;
  
  if (*(char *)(unaff_A2 + 6) == '\0') {
    *(undefined1 *)(unaff_A2 + 1) = 0;
  }
  else if (*(char *)(unaff_A2 + 6) == '\x01') {
    *(undefined1 *)(unaff_A2 + 1) = 4;
  }
  else if (*(char *)(unaff_A2 + 6) == '\x02') {
    *(undefined1 *)(unaff_A2 + 1) = 8;
  }
  else if (*(char *)(unaff_A2 + 6) == '\x03') {
    *(undefined1 *)(unaff_A2 + 1) = 0xc;
  }
  return;
}

