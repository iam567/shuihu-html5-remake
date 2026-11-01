/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001f91fe */

/* WARNING: Control flow encountered bad instruction data */

undefined8 FUN_001f91fe(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_0001da54();
  if ((DAT_00ff0f4e & 0x10) != 0) {
    FUN_00006520(0xffffffff,0x4ea,0xf);
    DAT_00ff0f4c = DAT_00ff0f4c | 0x20;
    return CONCAT44(in_D0,in_D1);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

