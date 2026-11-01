/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000153d4 */

void FUN_000153d4(void)

{
  ushort uVar1;
  int *piVar2;
  
  if (DAT_00ff6151 != '\0') {
    for (piVar2 = (int *)&DAT_00ff71a0; *piVar2 != 0x12345678; piVar2 = piVar2 + 2) {
      uVar1 = *(short *)(piVar2 + 1) + (short)*piVar2;
      if (*(ushort *)((int)piVar2 + 6) < uVar1) {
        uVar1 = *(ushort *)((int)piVar2 + 6);
      }
      *(ushort *)((int)piVar2 + 2) = uVar1;
    }
    for (piVar2 = (int *)&DAT_00ff71a0; *piVar2 != 0x12345678; piVar2 = piVar2 + 2) {
      DAT_00ff60ac = 3;
      FUN_0000b3ec();
    }
    DAT_00ff6151 = DAT_00ff6151 + -1;
    if (DAT_00ff6151 == '\0') {
      DAT_00ff6120 = 0xff;
      Ram00c00004 = 0x74000003;
      Ram00c00000 = DAT_00ff6008;
    }
  }
  return;
}

