/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00025184 */

void FUN_00025184(void)

{
  if ((DAT_00ff618f & 1) != 0) {
    DAT_00ff618f = DAT_00ff618f & 0xfe;
    FUN_00003386();
  }
  if ((DAT_00ff618f & 2) != 0) {
    DAT_00ff618f = DAT_00ff618f & 0xfd;
    FUN_000033ee();
  }
  if ((DAT_00ff618f & 4) != 0) {
    DAT_00ff618f = DAT_00ff618f & 0xfb;
    FUN_0000345e();
  }
  if ((DAT_00ff618f & 8) != 0) {
    DAT_00ff618f = DAT_00ff618f & 0xf7;
    FUN_000034c8();
  }
  return;
}

