/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0002618a */

void FUN_0002618a(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short *unaff_A2;
  
  if (DAT_00ff61b0 != '\0') {
    sVar4 = 0;
    sVar2 = 7;
    do {
      if ((&DAT_00ff61b4)[sVar4] != '\0') {
        sVar3 = *(short *)((int)&DAT_00ff71e0 + (int)(short)(sVar4 << 2)) - DAT_00ff6014;
        if ((sVar3 < 0x141) && (-0x21 < sVar3)) {
          sVar1 = *(short *)((int)&DAT_00ff71e0 + (short)(sVar4 << 2) + 2) - DAT_00ff6016;
          if ((sVar1 < 0xf1) && (-0x21 < sVar1)) {
            *unaff_A2 = sVar3 + 0x80;
            unaff_A2[1] = sVar1 + 0x80;
            sVar3 = 0x7c;
            if (0x20 < (byte)(&DAT_00ff61b4)[sVar4]) {
              sVar3 = 0x7d;
            }
            unaff_A2[2] = sVar3;
            unaff_A2 = unaff_A2 + 3;
            DAT_00ff6012 = DAT_00ff6012 + 1;
            if ((byte)(&DAT_00ff61b4)[sVar4] < 0x21) {
              (&DAT_00ff61b4)[sVar4] = (&DAT_00ff61b4)[sVar4] + '\x01';
            }
          }
        }
      }
      sVar4 = sVar4 + 1;
      sVar2 = sVar2 + -1;
    } while (sVar2 != -1);
  }
  return;
}

