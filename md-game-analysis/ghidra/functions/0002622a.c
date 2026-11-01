/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0002622a */

void FUN_0002622a(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  uint uVar4;
  short sVar5;
  short sVar6;
  short *unaff_A2;
  
  if ((DAT_00ffe1f7 == '\0') &&
     ((((DAT_00ff6085 == '\x04' || (DAT_00ff6085 == '\x13')) && (DAT_00ff605a != '\x01')) &&
      ((DAT_00ff6036 != '\0' && ((&DAT_00ff7180)[(short)(ushort)DAT_00ff6087] != 0xff)))))) {
    sVar5 = (ushort)(byte)(&DAT_00ff7180)[(short)(ushort)DAT_00ff6087] << 6;
    sVar1 = *(short *)((int)&DAT_00ffe780 + sVar5 + 2);
    sVar2 = *(short *)((int)&DAT_00ffe784 + (int)sVar5);
    uVar3 = *(ushort *)((int)&DAT_00ffe792 + (int)sVar5);
    uVar4 = uVar3 / 10;
    sVar6 = (short)(uVar4 % 10);
    sVar5 = (short)(uVar4 / 10);
    if (sVar5 != 0) {
      sVar5 = sVar5 + 0x7e;
      unaff_A2[2] = sVar5;
      *unaff_A2 = (sVar1 - DAT_00ff6014) + 0x84;
      unaff_A2[1] = (sVar2 - DAT_00ff6016) + 0x88;
      unaff_A2 = unaff_A2 + 3;
      DAT_00ff6012 = DAT_00ff6012 + 1;
    }
    if ((sVar6 != 0) || (sVar5 != 0)) {
      unaff_A2[2] = sVar6 + 0x7e;
      *unaff_A2 = (sVar1 - DAT_00ff6014) + 0x8c;
      unaff_A2[1] = (sVar2 - DAT_00ff6016) + 0x88;
      unaff_A2 = unaff_A2 + 3;
      DAT_00ff6012 = DAT_00ff6012 + 1;
    }
    unaff_A2[2] = uVar3 % 10 + 0x7e;
    *unaff_A2 = (sVar1 - DAT_00ff6014) + 0x94;
    unaff_A2[1] = (sVar2 - DAT_00ff6016) + 0x88;
    DAT_00ff6012 = DAT_00ff6012 + 1;
  }
  return;
}

