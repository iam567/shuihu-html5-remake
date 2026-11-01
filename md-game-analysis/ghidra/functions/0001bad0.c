/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001bad0 */

void FUN_0001bad0(void)

{
  byte bVar1;
  short sVar2;
  undefined2 *unaff_A2;
  undefined1 *puVar3;
  char *pcVar4;
  undefined4 *puVar5;
  char cVar6;
  
  if ((DAT_00ff6189 & 8) != 0) {
    puVar3 = &DAT_00ff9000;
    if ((DAT_00ff6188 & 1) != 0) {
      puVar3 = &DAT_00ffe400;
    }
    bVar1 = puVar3[(short)(ushort)DAT_00ff617a];
    pcVar4 = &DAT_00ff8000;
    puVar5 = &DAT_0001b3c8;
    sVar2 = 0x13;
    do {
      if (*pcVar4 == '\0') {
        return;
      }
      cVar6 = '\0';
      if (bVar1 < 0x70) {
        cVar6 = bVar1 == pcVar4[0x26];
        if (bVar1 == pcVar4[0x27]) {
          cVar6 = cVar6 + '\x01';
        }
        if (bVar1 == pcVar4[0x28]) {
          cVar6 = cVar6 + '\x01';
        }
        if (bVar1 == pcVar4[0x29]) {
          cVar6 = cVar6 + '\x01';
        }
      }
      else if (bVar1 < 0x80) {
        if (bVar1 == pcVar4[0x2a]) {
          cVar6 = '\x01';
        }
      }
      else {
        cVar6 = bVar1 == pcVar4[8];
        if (bVar1 == pcVar4[9]) {
          cVar6 = cVar6 + '\x01';
        }
        if (bVar1 == pcVar4[10]) {
          cVar6 = cVar6 + '\x01';
        }
        if (bVar1 == pcVar4[0xb]) {
          cVar6 = cVar6 + '\x01';
        }
      }
      if (cVar6 != '\0') {
        *unaff_A2 = *(undefined2 *)puVar5;
        unaff_A2[1] = *(undefined2 *)((int)puVar5 + 2);
        unaff_A2[2] = (byte)(cVar6 - 1) + 100;
        unaff_A2 = unaff_A2 + 3;
        DAT_00ff6012 = DAT_00ff6012 + 1;
      }
      pcVar4 = pcVar4 + 0x40;
      puVar5 = puVar5 + 1;
      sVar2 = sVar2 + -1;
    } while (sVar2 != -1);
  }
  return;
}

