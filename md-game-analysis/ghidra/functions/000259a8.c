/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000259a8 */

void FUN_000259a8(void)

{
  ushort uVar1;
  short sVar2;
  ushort *puVar3;
  ushort *puVar4;
  ushort *puVar5;
  
  Ram00c00004 = 0xc0000000;
  sVar2 = 0x2f;
  puVar3 = &DAT_00ffef00;
  puVar4 = &DAT_00ffef80;
  puVar5 = (ushort *)&DAT_00ff71a0;
  do {
    uVar1 = *puVar3;
    *puVar5 = uVar1;
    uVar1 = (uVar1 >> 9 & 0xe) << 8 | (uVar1 >> 5 & 0xe) << 4 | uVar1 >> 1 & 0xe;
    *puVar3 = uVar1;
    *puVar4 = uVar1;
    Ram00c00000 = uVar1;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  } while (sVar2 != -1);
  DAT_00ff6001 = 0xff;
  return;
}

