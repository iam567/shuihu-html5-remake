/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006790 */

void FUN_00006790(void)

{
  uint uVar1;
  short sVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar1 = DAT_00ffe1e0;
  uVar3 = 0;
  pcVar4 = (char *)&DAT_00ffe780;
  sVar2 = 0x1d;
  do {
    if ((*pcVar4 != '\0') && ((uVar1 & 1 << (uVar3 & 0x1f)) != 0)) {
      if (pcVar4[0xc] == '\0') {
        if (pcVar4[6] == '\0') {
          pcVar4[1] = '\0';
        }
        else if (pcVar4[6] == '\x01') {
          pcVar4[1] = '\x04';
        }
        else if (pcVar4[6] == '\x02') {
          pcVar4[1] = '\b';
        }
        else if (pcVar4[6] == '\x03') {
          pcVar4[1] = '\f';
        }
        pcVar4[1] = (((byte)DAT_00ff6010 & 0x3f) >> 4) + pcVar4[1];
      }
      else {
        pcVar4[1] = '\x04';
      }
    }
    uVar3 = (uint)(byte)((char)uVar3 + 1);
    pcVar4 = pcVar4 + 0x40;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}

