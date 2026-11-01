/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001646a */

void FUN_0001646a(void)

{
  undefined2 *unaff_A3;
  undefined1 *unaff_A5;
  
  *unaff_A5 = 3;
  *(undefined2 *)(unaff_A5 + 2) = *unaff_A3;
  *(ushort *)(unaff_A5 + 4) = unaff_A3[1] - (ushort)*(byte *)(unaff_A3 + 4);
  return;
}

