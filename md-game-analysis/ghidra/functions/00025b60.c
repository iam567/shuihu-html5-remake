/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00025b60 */

void FUN_00025b60(void)

{
  short sVar1;
  undefined2 uVar2;
  undefined4 *unaff_A2;
  undefined4 *puVar3;
  
  if (DAT_00ff61a8 != 0) {
    if (DAT_00ff61a8 < 0x21) {
      sVar1 = DAT_00ff61a9 - 1;
      if (DAT_00ff61a9 != 0) {
        puVar3 = &DAT_00ff71e0;
        do {
          *unaff_A2 = *puVar3;
          uVar2 = 0x6b;
          if ((8 < DAT_00ff61a8) && (uVar2 = 0x6c, 0x10 < DAT_00ff61a8)) {
            uVar2 = 0x6d;
          }
          *(undefined2 *)(unaff_A2 + 1) = uVar2;
          if ((DAT_00ff61a8 & 1) == 0) {
            *(short *)((int)puVar3 + 2) = *(short *)((int)puVar3 + 2) + 1;
          }
          unaff_A2 = (undefined4 *)((int)unaff_A2 + 6);
          DAT_00ff6012 = DAT_00ff6012 + 1;
          puVar3 = puVar3 + 1;
          sVar1 = sVar1 + -1;
        } while (sVar1 != -1);
        DAT_00ff61a8 = DAT_00ff61a8 + 1;
      }
    }
    else {
      DAT_00ff61a8 = 0;
      DAT_00ff603d = DAT_00ff603d | 2;
    }
  }
  return;
}

