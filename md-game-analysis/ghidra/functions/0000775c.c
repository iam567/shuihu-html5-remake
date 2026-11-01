/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000775c */

void FUN_0000775c(void)

{
  short sVar1;
  uint uVar2;
  char *pcVar3;
  
  if (DAT_00ff6031 == '\0') {
    uVar2 = 0;
    pcVar3 = &DAT_00ffe080;
    sVar1 = 7;
    do {
      if ((*pcVar3 == '\0') || (3 < (byte)pcVar3[6])) goto LAB_00007834;
      DAT_00ff601e._0_1_ = DAT_00ff601e._0_1_ | '\x01' << (uVar2 & 7);
      FUN_00007982();
      if (((DAT_00ff6037 & 1) == 0) &&
         ((FUN_00007842(), (DAT_00ff6037 & 1) == 0 &&
          (sVar1 = FUN_00007a32(), (DAT_00ff6037 & 1) == 0)))) {
        if (pcVar3[6] == '\0') {
          if (*(short *)(pcVar3 + 10) == *(short *)(pcVar3 + 4)) goto LAB_0000782e;
          *(short *)(pcVar3 + 4) = *(short *)(pcVar3 + 4) + -1;
        }
        else if (pcVar3[6] == '\x01') {
          if (*(short *)(pcVar3 + 0xe) == *(short *)(pcVar3 + 4)) goto LAB_0000782e;
          *(short *)(pcVar3 + 4) = *(short *)(pcVar3 + 4) + 1;
        }
        else if (pcVar3[6] == '\x02') {
          if (*(short *)(pcVar3 + 8) == *(short *)(pcVar3 + 2)) goto LAB_0000782e;
          *(short *)(pcVar3 + 2) = *(short *)(pcVar3 + 2) + -1;
        }
        else {
          if (*(short *)(pcVar3 + 0xc) == *(short *)(pcVar3 + 2)) goto LAB_0000782e;
          *(short *)(pcVar3 + 2) = *(short *)(pcVar3 + 2) + 1;
        }
      }
      else {
LAB_0000782e:
        sVar1 = FUN_0000789e();
      }
LAB_00007834:
      uVar2 = (uint)(byte)((char)uVar2 + 1);
      pcVar3 = pcVar3 + 0x10;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
  }
  return;
}

