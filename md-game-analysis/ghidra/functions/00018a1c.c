/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00018a1c */

void FUN_00018a1c(void)

{
  undefined2 *unaff_A2;
  
  if ((DAT_00ff615d & 2) != 0) {
    *unaff_A2 = DAT_00ff6164;
    unaff_A2[1] = DAT_00ff6166;
    unaff_A2[2] = 0x52;
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

