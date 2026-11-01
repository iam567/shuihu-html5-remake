/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000010e0 */

void FUN_000010e0(void)

{
  short in_D0w;
  short in_D1w;
  uint unaff_D2;
  undefined2 *unaff_A2;
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  
  puVar1 = (undefined2 *)((int)&DAT_00ffef00 + (int)(short)(in_D1w << 1));
  puVar3 = (undefined2 *)((int)&DAT_00ffef80 + (int)(short)(in_D1w << 1));
  do {
    puVar2 = puVar1;
    if ((unaff_D2 & 0x80) != 0) {
      puVar2 = puVar1 + 1;
      *puVar1 = *unaff_A2;
    }
    puVar4 = puVar3;
    if ((unaff_D2 & 8) != 0) {
      if ((unaff_D2 & 1) == 0) {
        if ((unaff_D2 & 2) == 0) {
          puVar4 = puVar3 + 1;
          *puVar3 = 0xeee;
        }
        else {
          puVar4 = puVar3 + 1;
          *puVar3 = *unaff_A2;
        }
      }
      else {
        puVar4 = puVar3 + 1;
        *puVar3 = 0;
      }
    }
    unaff_A2 = unaff_A2 + 1;
    in_D0w = in_D0w + -1;
    puVar1 = puVar2;
    puVar3 = puVar4;
  } while (in_D0w != -1);
  DAT_00ff6001 = 0xff;
  return;
}

