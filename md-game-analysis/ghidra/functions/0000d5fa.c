/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000d5fa */

void FUN_0000d5fa(void)

{
  short sVar1;
  short sVar2;
  short unaff_D3w;
  undefined2 unaff_D4w;
  short sVar3;
  undefined2 unaff_D5w;
  short sVar4;
  int *piVar5;
  int *piVar6;
  
  FUN_00009898();
  piVar5 = (int *)&DAT_0000d21e;
  if (((&DAT_00ffe7a4)[(short)((ushort)DAT_00ff606b << 6)] != '\x1a') &&
     (piVar5 = (int *)&DAT_0000d252, (&DAT_00ffe7a4)[(short)((ushort)DAT_00ff606b << 6)] != '\x1b'))
  {
    piVar5 = (int *)&DAT_0000d2b6;
  }
  sVar3 = CONCAT11((char)((ushort)unaff_D4w >> 8),DAT_00ff6088);
  sVar4 = CONCAT11((char)((ushort)unaff_D5w >> 8),DAT_00ff6089);
  while (*piVar5 != 0x12345678) {
    sVar1 = *(short *)piVar5 + sVar3;
    piVar6 = piVar5 + 1;
    sVar2 = (short)*piVar5 + sVar4;
    piVar5 = piVar6;
    if ((((-1 < sVar1) && ((char)sVar1 < DAT_00ffe108)) && (-1 < sVar2)) &&
       ((char)sVar2 < DAT_00ffe109)) {
      FUN_00006902();
      (&DAT_00ff5000)[unaff_D3w] = 0xff;
    }
  }
  return;
}

