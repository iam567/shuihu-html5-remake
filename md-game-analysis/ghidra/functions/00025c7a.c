/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00025c7a */

void FUN_00025c7a(void)

{
  short sVar1;
  undefined2 uVar2;
  undefined4 *unaff_A2;
  undefined4 *puVar3;
  
  if (DAT_00ff61ac != 0) {
    if (DAT_00ff61ac < 0x41) {
      sVar1 = DAT_00ff61ad - 1;
      if (DAT_00ff61ad != 0) {
        puVar3 = &DAT_00ff71e0;
        do {
          *unaff_A2 = *puVar3;
          uVar2 = 0x71;
          if ((((8 < DAT_00ff61ac) && (uVar2 = 0x72, 0x10 < DAT_00ff61ac)) &&
              (uVar2 = 0x73, 0x18 < DAT_00ff61ac)) &&
             (((uVar2 = 0x74, 0x20 < DAT_00ff61ac && (uVar2 = 0x71, 0x28 < DAT_00ff61ac)) &&
              ((uVar2 = 0x72, 0x30 < DAT_00ff61ac && (uVar2 = 0x73, 0x38 < DAT_00ff61ac)))))) {
            uVar2 = 0x74;
          }
          *(undefined2 *)(unaff_A2 + 1) = uVar2;
          unaff_A2 = (undefined4 *)((int)unaff_A2 + 6);
          DAT_00ff6012 = DAT_00ff6012 + 1;
          puVar3 = puVar3 + 1;
          sVar1 = sVar1 + -1;
        } while (sVar1 != -1);
        DAT_00ff61ac = DAT_00ff61ac + 1;
      }
    }
    else {
      DAT_00ff61ac = 0;
      DAT_00ff603d = DAT_00ff603d | 2;
    }
  }
  return;
}

