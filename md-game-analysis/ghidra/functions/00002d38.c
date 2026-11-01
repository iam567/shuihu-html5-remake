/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00002d38 */

void FUN_00002d38(void)

{
  short in_D0w;
  short in_D1w;
  undefined2 *unaff_A2;
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  Ram00c00004 = 0x8134;
  Ram00c00004 = 0xc0000000;
  puVar1 = (undefined2 *)((int)&DAT_00ffef00 + (int)(short)(in_D1w << 1));
  puVar2 = (undefined2 *)((int)&DAT_00ffef80 + (int)(short)(in_D1w << 1));
  do {
    Ram00c00000 = 0;
    *puVar2 = 0;
    *puVar1 = *unaff_A2;
    in_D0w = in_D0w + -1;
    unaff_A2 = unaff_A2 + 1;
    puVar1 = puVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (in_D0w != -1);
  Ram00c00004 = 0x8174;
  return;
}

