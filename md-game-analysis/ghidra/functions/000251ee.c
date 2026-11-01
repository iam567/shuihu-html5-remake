/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000251ee */

void FUN_000251ee(void)

{
  if ((DAT_00ff615c & 1) != 0) {
    DAT_00ff615c = DAT_00ff615c & 0xfe;
    FUN_00006e1e();
    FUN_00003386();
  }
  if ((DAT_00ff615c & 2) != 0) {
    DAT_00ff615c = DAT_00ff615c & 0xfd;
    FUN_00006e92();
    FUN_000033ee();
  }
  if ((DAT_00ff615c & 4) != 0) {
    DAT_00ff615c = DAT_00ff615c & 0xfb;
    FUN_00006d28();
    FUN_0000345e();
  }
  if ((DAT_00ff615c & 8) != 0) {
    DAT_00ff615c = DAT_00ff615c & 0xf7;
    FUN_00006d9e();
    FUN_000034c8();
  }
  return;
}

