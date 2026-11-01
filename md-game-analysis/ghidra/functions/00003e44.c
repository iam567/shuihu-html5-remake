/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003e44 */

void FUN_00003e44(void)

{
  short sVar1;
  short extraout_D1w;
  uint uVar2;
  char *pcVar3;
  int *piVar4;
  char *pcVar5;
  
  if (DAT_00ff6031 != '\0') {
    DAT_00ff6037 = DAT_00ff6037 & 0xfe;
    pcVar3 = &DAT_00ffe000;
    piVar4 = &DAT_00ff7018;
    pcVar5 = (char *)0xff7058;
    uVar2 = 0;
    sVar1 = 0xf;
    do {
      if ((*pcVar3 != '\0') && (*(short *)piVar4 != 0)) {
        if (*(int *)(pcVar3 + 2) == *piVar4) {
          pcVar3[1] = *pcVar5;
          DAT_00ff601e = DAT_00ff601e | (ushort)(1 << (uVar2 & 0x1f));
          pcVar3[6] = -1;
        }
        else {
          if (DAT_00ffe10d == '\0') {
            if ((DAT_00ff603e & 1) == 0) {
              FUN_00003f30();
              sVar1 = FUN_00003fea();
            }
          }
          else {
            do {
              FUN_00003f30();
            } while (extraout_D1w != 0);
            sVar1 = FUN_00003fea();
          }
          DAT_00ff6037 = DAT_00ff6037 | 1;
        }
      }
      piVar4 = piVar4 + 1;
      pcVar5 = pcVar5 + 1;
      pcVar3 = pcVar3 + 0x10;
      uVar2 = (uint)(byte)((char)uVar2 + 1);
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    if ((DAT_00ff6037 & 1) == 0) {
      DAT_00ff6031 = '\0';
      DAT_00ff603d = DAT_00ff603d | 2;
    }
    else {
      DAT_00ff603e = DAT_00ff603e + 1;
    }
  }
  return;
}

