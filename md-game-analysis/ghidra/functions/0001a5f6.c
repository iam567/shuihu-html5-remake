/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001a5f6 */

undefined8 FUN_0001a5f6(void)

{
  int iVar1;
  uint uVar2;
  undefined4 in_D0;
  short sVar3;
  undefined4 in_D1;
  uint uVar4;
  short sVar5;
  
  iVar1 = *(int *)(&DAT_000dc84a + (short)((DAT_00ffe100 >> 8) << 2));
  uVar2 = *(uint *)(&DAT_00ffe500 + (short)((DAT_00ffe100 >> 8) << 2));
  uVar4 = 0;
  sVar3 = 0x1f;
  do {
    if (((uVar2 & 1 << (uVar4 & 0x1f)) != 0) &&
       (sVar5 = (short)uVar4 << 3, *(ushort *)(iVar1 + sVar5) == DAT_00ffe100)) {
      (&DAT_00ffd000)[*(short *)(iVar1 + 2 + (int)sVar5)] = 0x50;
    }
    uVar4 = uVar4 + 1;
    sVar3 = sVar3 + -1;
  } while (sVar3 != -1);
  return CONCAT44(in_D0,in_D1);
}

