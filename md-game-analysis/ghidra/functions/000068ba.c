/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000068ba */

void FUN_000068ba(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  short *psVar4;
  
  uVar2 = (ushort)DAT_00ffe108;
  uVar1 = (ushort)(byte)(DAT_00ffe109 - 1);
  uVar3 = 0;
  psVar4 = &DAT_00ff7100;
  do {
    *psVar4 = uVar3 * uVar2;
    uVar3 = (ushort)(byte)((char)uVar3 + 1);
    uVar1 = uVar1 - 1;
    psVar4 = psVar4 + 1;
  } while (uVar1 != 0xffff);
  return;
}

