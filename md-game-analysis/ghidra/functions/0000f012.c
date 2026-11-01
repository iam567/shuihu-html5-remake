/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000f012 */

void FUN_0000f012(void)

{
  byte bVar1;
  
  DAT_00ff6120 = 0;
  FUN_00003ae4();
  Seed_e50();
  FUN_00006f50();
  FUN_0000f1ba();
  while( true ) {
    bVar1 = FUN_00000e40();
    if (bVar1 == 0x80) break;
    DAT_00ff600a = *(short *)((int)&PTR_DAT_0000ecf0 + (int)(short)((ushort)bVar1 << 1)) +
                   DAT_00ff600a;
    DAT_00ff603a = 1;
    FUN_00003a82();
  }
  DAT_00ff6120 = 0xff;
  return;
}

