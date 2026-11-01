/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00018c18 */

void FUN_00018c18(void)

{
  short sVar1;
  ushort uVar2;
  undefined4 *puVar3;
  
  DAT_00ff613f = (&DAT_00ff8007)[(short)((ushort)DAT_00ff6163 << 6)];
  DAT_00ff60b6 = 0x22;
  DAT_00ff60b4 = 0xa00a;
  FUN_000144b8();
  DAT_00ff60b4 = 0x1001;
  FUN_000144b8();
  Seed_1028();
  sVar1 = 0xb;
  puVar3 = (undefined4 *)&DAT_00ff1000;
  do {
    *puVar3 = 0;
    sVar1 = sVar1 + -1;
    puVar3 = puVar3 + 1;
  } while (sVar1 != -1);
  uVar2 = (ushort)DAT_00ff6163;
  FUN_00014c80();
  *(undefined2 *)(&DAT_00ff8012 + (short)(uVar2 << 6)) =
       *(undefined2 *)(&DAT_00ff801e + (short)(uVar2 << 6));
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_0001762e();
  FUN_00002846();
  return;
}

