/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000075aa */

void FUN_000075aa(void)

{
  byte *pbVar1;
  
  if ((DAT_00ff606e != '\0') && (DAT_00ff606d == '\0')) {
    pbVar1 = DAT_00ff6078 + 1;
    if (*DAT_00ff6078 == 0xff) {
      DAT_00ff606e = '\0';
    }
    else {
      DAT_00ff6052 = (ushort)*DAT_00ff6078;
      DAT_00ff6078 = DAT_00ff6078 + 2;
      DAT_00ff6054 = (ushort)*pbVar1;
      DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
      DAT_00ff606d = '\x01';
    }
  }
  return;
}

