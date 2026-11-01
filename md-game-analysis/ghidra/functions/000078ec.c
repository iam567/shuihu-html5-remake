/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000078ec */

void FUN_000078ec(void)

{
  int unaff_A2;
  
  if (*(char *)(unaff_A2 + 6) == '\0') {
    *(undefined1 *)(unaff_A2 + 6) = 1;
    return;
  }
  if (*(char *)(unaff_A2 + 6) == '\x01') {
    *(undefined1 *)(unaff_A2 + 6) = 0;
    return;
  }
  if (*(char *)(unaff_A2 + 6) == '\x02') {
    *(undefined1 *)(unaff_A2 + 6) = 3;
    return;
  }
  if (*(char *)(unaff_A2 + 6) == '\x03') {
    *(undefined1 *)(unaff_A2 + 6) = 2;
  }
  return;
}

