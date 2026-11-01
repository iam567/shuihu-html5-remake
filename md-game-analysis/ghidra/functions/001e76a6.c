/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e76a6 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_001e76a6(void)

{
  DAT_00ff6f60 = DAT_00ff6f55;
  _DAT_00ff6f54 = _DAT_00ff6f54 & 0xff00;
  FUN_001e7720();
  if (DAT_00ff6f61 == '\0') {
    _DAT_00ff6f54 = 0;
  }
  DAT_00ff6f68 = DAT_00ff6f57;
  _DAT_00ff6f56 = _DAT_00ff6f56 & 0xff00;
  FUN_001e7720();
  if (DAT_00ff6f69 == '\0') {
    _DAT_00ff6f56 = 0;
  }
  DAT_00ff6f70 = DAT_00ff6f59;
  _DAT_00ff6f58 = _DAT_00ff6f58 & 0xff00;
  FUN_001e7720();
  if (DAT_00ff6f71 == '\0') {
    _DAT_00ff6f58 = 0;
  }
  return;
}

