/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e4150 */

void FUN_001e4150(void)

{
  if ((DAT_00ff6d08 != '\0') && (DAT_00ff6d0a = DAT_00ff6d0a + -1, DAT_00ff6d0a == '\0')) {
    DAT_00ff6d0a = DAT_00ff6d09;
    DAT_00ff6d07 = (&DAT_001e41a0)[(short)DAT_00ff6d0b];
    if (DAT_00ff6d07 < '\0') {
      DAT_00ff6d08 = '\0';
      DAT_00ff6d04 = 0;
      DAT_00ff6d05 = 0xff;
    }
    else {
      DAT_00ff6d0d = *(undefined1 *)((int)&PTR_DAT_001e41a1 + (int)(short)DAT_00ff6d0b);
      DAT_00ff6d0b = DAT_00ff6d0b + '\x02';
    }
  }
  return;
}

