/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000148e2 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000148e2(void)

{
  int iVar1;
  short sVar2;
  short sVar3;
  char cVar4;
  byte bVar5;
  undefined2 *unaff_A2;
  int *piVar6;
  
  if (DAT_00ff6149 != '\0') {
    cVar4 = '\0';
    bVar5 = 0;
    piVar6 = (int *)&DAT_00ff5000;
    sVar2 = 0x1f;
    do {
      iVar1 = *piVar6;
      if (iVar1 != _DAT_00ff6048) {
        cVar4 = cVar4 + '\x01';
        *(short *)piVar6 = *(short *)(piVar6 + 1) + *(short *)piVar6;
        *(short *)((int)piVar6 + 2) = *(short *)((int)piVar6 + 6) + *(short *)((int)piVar6 + 2);
        if ((((0x60 < *(short *)piVar6) && (*(short *)piVar6 < 0x1c0)) &&
            (sVar3 = (short)iVar1, 0x60 < sVar3)) && (sVar3 < 0x170)) {
          *unaff_A2 = *(undefined2 *)piVar6;
          unaff_A2[1] = (short)*piVar6;
          unaff_A2[2] = 0x43;
          if (bVar5 < 0x10) {
            unaff_A2[2] = 0x44;
          }
          DAT_00ff6012 = DAT_00ff6012 + 1;
          unaff_A2 = unaff_A2 + 3;
        }
      }
      piVar6 = piVar6 + 2;
      bVar5 = bVar5 + 1;
      sVar2 = sVar2 + -1;
    } while (sVar2 != -1);
    if (cVar4 == '\0') {
      DAT_00ff6149 = '\0';
      DAT_00ff6103 = 2;
      DAT_00ff614c = 1;
      DAT_00ff60aa = 0;
    }
  }
  return;
}

