/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003b66 */

undefined4 FUN_00003b66(void)

{
  undefined4 in_D0;
  short sVar1;
  uint uVar2;
  char *pcVar3;
  
  if ((((DAT_00ff6033 & 1) == 0) && (DAT_00ff6031 == '\0')) &&
     ((DAT_00ff6030 == ' ' || (DAT_00ff6030 == '\x10')))) {
    pcVar3 = &DAT_00ffe000;
    uVar2 = 0;
    sVar1 = 7;
    do {
      if (*pcVar3 != '\0') {
        if (pcVar3[6] == '\0') {
          pcVar3[1] = '\0';
        }
        else if (pcVar3[6] == '\x01') {
          pcVar3[1] = '\x04';
        }
        else if (pcVar3[6] == '\x02') {
          pcVar3[1] = '\b';
        }
        else if (pcVar3[6] == '\x03') {
          pcVar3[1] = '\f';
        }
        else if (pcVar3[6] == '\x04') {
          pcVar3[1] = '\b';
        }
        else if (pcVar3[6] == '\x05') {
          pcVar3[1] = '\f';
        }
        else if (pcVar3[6] == '\x06') {
          pcVar3[1] = '\b';
        }
        else {
          if (pcVar3[6] != '\a') goto LAB_00003c66;
          pcVar3[1] = '\f';
        }
        DAT_00ff601e._1_1_ = (byte)DAT_00ff601e | '\x01' << (uVar2 & 7);
        pcVar3[1] = ((byte)(DAT_00ff6030 - 1U) >> 4) + pcVar3[1];
        sVar1 = FUN_00003c78();
      }
LAB_00003c66:
      pcVar3 = pcVar3 + 0x10;
      uVar2 = (uint)(byte)((char)uVar2 + 1);
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
  }
  return in_D0;
}

