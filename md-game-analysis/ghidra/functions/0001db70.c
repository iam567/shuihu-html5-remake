/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001db70 */

/* WARNING: Control flow encountered bad instruction data */

void FUN_0001db70(void)

{
  int in_A0;
  
  *(ushort *)(in_A0 + -2) = *(ushort *)(in_A0 + -2) | 0x240;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

