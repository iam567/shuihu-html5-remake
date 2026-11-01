/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000916c */

void FUN_0000916c(void)

{
  int unaff_A2;
  
  DAT_00ff610c = 0xff;
  if (*(char *)(unaff_A2 + 0x27) != '\0') {
    DAT_00ff610c = *(undefined1 *)
                    ((int)&PTR_DAT_00028e5b +
                    (int)(short)((ushort)(byte)(*(char *)(unaff_A2 + 0x27) - 1) << 3));
  }
  return;
}

