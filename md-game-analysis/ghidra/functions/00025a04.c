/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00025a04 */

void FUN_00025a04(void)

{
  undefined2 uVar1;
  short sVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  
  Ram00c00004 = 0xc0000000;
  sVar2 = 0x2f;
  puVar3 = &DAT_00ffef00;
  puVar4 = &DAT_00ffef80;
  puVar5 = (undefined2 *)&DAT_00ff71a0;
  do {
    uVar1 = *puVar5;
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

