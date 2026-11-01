/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009df8 */

void FUN_00009df8(void)

{
  short in_D0w;
  short in_D1w;
  ushort uVar1;
  undefined2 *unaff_A2;
  undefined2 *puVar2;
  undefined2 *puVar3;
  
  uVar1 = in_D1w << 1;
  Ram00c00004 = (uint)uVar1 << 0x10 | 0xc0000000;
  puVar2 = (undefined2 *)((int)&DAT_00ffef00 + (int)(short)uVar1);
  puVar3 = (undefined2 *)((int)&DAT_00ffef80 + (int)(short)uVar1);
  do {
    Ram00c00000 = *unaff_A2;
    *puVar2 = *unaff_A2;
    *puVar3 = *unaff_A2;
    in_D0w = in_D0w + -1;
    unaff_A2 = unaff_A2 + 1;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  } while (in_D0w != -1);
  return;
}

