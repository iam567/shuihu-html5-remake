/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00004ab4 */

void FUN_00004ab4(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  undefined2 unaff_D6w;
  int *piVar4;
  int *piVar5;
  
  sVar3 = (ushort)DAT_00ff609f << 6;
  if (*(char *)((int)&DAT_00ffe78c + (int)sVar3) == '\0') {
    piVar4 = *(int **)(&DAT_0000aeb2 +
                      (short)(CONCAT11((char)((ushort)unaff_D6w >> 8),(&DAT_00ffe7a4)[sVar3] + -1)
                             << 2));
    do {
      if (*piVar4 == 0x12345678) {
        return;
      }
      uVar1 = *(short *)piVar4 + (*(ushort *)((int)&DAT_00ffe780 + sVar3 + 2) >> 5);
      piVar5 = piVar4 + 1;
      uVar2 = (short)*piVar4 + (*(ushort *)((int)&DAT_00ffe784 + (int)sVar3) >> 5);
      piVar4 = piVar5;
    } while (((((short)uVar1 < 0) || (DAT_00ffe108 <= (char)uVar1)) || ((short)uVar2 < 0)) ||
            (((DAT_00ffe109 <= (char)uVar2 ||
              (uVar1 != *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff606b << 6) + 2) >>
                        5)) ||
             (uVar2 != *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff606b << 6)) >>
                       5))));
  }
  return;
}

