/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00025bee */

void FUN_00025bee(void)

{
  short sVar1;
  undefined2 uVar2;
  undefined4 *unaff_A2;
  undefined4 *puVar3;
  
  if (DAT_00ff61aa != 0) {
    if (DAT_00ff61aa < 0x19) {
      sVar1 = DAT_00ff61ab - 1;
      if (DAT_00ff61ab != 0) {
        puVar3 = &DAT_00ff71e0;
        do {
          *unaff_A2 = *puVar3;
          uVar2 = 0x6e;
          if (((6 < DAT_00ff61aa) && (uVar2 = 0x70, 0xc < DAT_00ff61aa)) &&
             (uVar2 = 0x6f, 0x12 < DAT_00ff61aa)) {
            uVar2 = 0x6e;
          }
          *(undefined2 *)(unaff_A2 + 1) = uVar2;
          unaff_A2 = (undefined4 *)((int)unaff_A2 + 6);
          DAT_00ff6012 = DAT_00ff6012 + 1;
          puVar3 = puVar3 + 1;
          sVar1 = sVar1 + -1;
        } while (sVar1 != -1);
        DAT_00ff61aa = DAT_00ff61aa + 1;
      }
    }
    else {
      DAT_00ff61aa = 0;
      DAT_00ff603d = DAT_00ff603d | 2;
    }
  }
  return;
}

