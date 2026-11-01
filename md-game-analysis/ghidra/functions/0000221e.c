/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000221e */

void FUN_0000221e(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  ushort uVar4;
  char cVar5;
  short sVar6;
  short *unaff_A2;
  char *pcVar7;
  undefined *puVar8;
  
  puVar8 = &DAT_00002330;
  pcVar7 = (char *)&DAT_00ffe780;
  cVar5 = '\0';
  sVar3 = 0x1d;
  do {
    if ((*pcVar7 != '\0') && (cVar5 != DAT_00ff606b)) {
      sVar2 = *(short *)(pcVar7 + 2) - DAT_00ff6014;
      sVar6 = sVar2 + 0x80;
      if ((0x60 < sVar6) &&
         (((sVar6 < 0x1c0 && (sVar1 = (*(short *)(pcVar7 + 4) - DAT_00ff6016) + 0x80, 0x60 < sVar1))
          && (sVar1 < 0x160)))) {
        if (pcVar7[0x25] == '\0') {
          if (pcVar7[0x1c] != '\0') {
            pcVar7[0x1c] = pcVar7[0x1c] + -1;
            sVar6 = sVar2 + 0x78;
          }
        }
        else {
          pcVar7[0x25] = pcVar7[0x25] + -1;
          sVar6 = *(short *)(&DAT_00002300 + (short)((ushort)(byte)pcVar7[0x25] << 1)) + sVar6;
        }
        *unaff_A2 = sVar6;
        unaff_A2[1] = sVar1;
        uVar4 = *(ushort *)(puVar8 + (short)((ushort)(byte)pcVar7[1] << 1));
        if ((pcVar7[0x1d] != '\0') && (uVar4 = uVar4 | 0x6000, pcVar7[0x1d] != -1)) {
          pcVar7[0x1d] = pcVar7[0x1d] + -1;
        }
        unaff_A2[2] = uVar4;
        DAT_00ff6012 = DAT_00ff6012 + 1;
        unaff_A2 = unaff_A2 + 3;
      }
    }
    puVar8 = puVar8 + 0x24;
    pcVar7 = pcVar7 + 0x40;
    cVar5 = cVar5 + '\x01';
    sVar3 = sVar3 + -1;
  } while (sVar3 != -1);
  return;
}

