/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003cb0 */

void FUN_00003cb0(void)

{
  short sVar1;
  uint uVar2;
  char *pcVar3;
  short *psVar4;
  char *pcVar5;
  
  if ((DAT_00ff603b != '\0') && (DAT_00ff6030 == '\0')) {
    DAT_00ff6037 = DAT_00ff6037 & 0xfe;
    pcVar3 = &DAT_00ffe000;
    psVar4 = (short *)&DAT_00ff7000;
    pcVar5 = (char *)0xff7010;
    uVar2 = 0;
    sVar1 = 7;
    do {
      if (*pcVar3 != '\0') {
        if (*psVar4 != 0) {
          if (CONCAT11((char)(*(ushort *)(pcVar3 + 2) >> 5),(char)(*(ushort *)(pcVar3 + 4) >> 5)) !=
              *psVar4) {
            sVar1 = FUN_00003d6e();
            DAT_00ff6037 = DAT_00ff6037 | 1;
            goto LAB_00003d36;
          }
          pcVar3[1] = *pcVar5;
          DAT_00ff601e = DAT_00ff601e | (ushort)(1 << (uVar2 & 0x1f));
        }
        pcVar3[6] = -1;
      }
LAB_00003d36:
      psVar4 = psVar4 + 1;
      pcVar5 = pcVar5 + 1;
      pcVar3 = pcVar3 + 0x10;
      uVar2 = (uint)(byte)((char)uVar2 + 1);
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    if ((DAT_00ff6037 & 1) == 0) {
      DAT_00ff603b = '\0';
      DAT_00ff603d = DAT_00ff603d | 2;
    }
    else {
      DAT_00ff6030 = ' ';
    }
  }
  return;
}

