/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000079fa */

void FUN_000079fa(void)

{
  int unaff_A2;
  
  if (*(char *)(unaff_A2 + 6) == '\0') {
    return;
  }
  if (*(char *)(unaff_A2 + 6) == '\x01') {
    return;
  }
  if (*(char *)(unaff_A2 + 6) == '\x02') {
    return;
  }
  return;
}

