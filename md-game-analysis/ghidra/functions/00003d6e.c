/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003d6e */

void FUN_00003d6e(void)

{
  char cVar1;
  int unaff_A2;
  char *unaff_A3;
  
  cVar1 = (char)(*(ushort *)(unaff_A2 + 2) >> 5);
  if (cVar1 == *unaff_A3) {
    if (unaff_A3[1] < (char)(*(ushort *)(unaff_A2 + 4) >> 5)) {
      *(undefined1 *)(unaff_A2 + 6) = 0;
    }
    else {
      *(undefined1 *)(unaff_A2 + 6) = 1;
    }
  }
  else if (cVar1 < *unaff_A3) {
    *(undefined1 *)(unaff_A2 + 6) = 3;
  }
  else {
    *(undefined1 *)(unaff_A2 + 6) = 2;
  }
  return;
}

