/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001c898 */

void FUN_0001c898(void)

{
  byte *pbVar1;
  byte bVar2;
  ushort uVar3;
  short sVar4;
  uint uVar5;
  byte *pbVar6;
  char *pcVar7;
  undefined4 *puVar8;
  
  pbVar1 = *(byte **)(&DAT_0001c98a + (short)((ushort)DAT_00ffe10f << 2));
  DAT_00ffe1ec = 0;
  DAT_00ffe1e8 = 0;
  bVar2 = *pbVar1;
  DAT_00ffe1fa = (ushort)bVar2;
  if (pbVar1[1] != 0) {
    DAT_00ffe1ec = 0;
    for (; (char)bVar2 < '\f'; bVar2 = bVar2 + 1) {
      DAT_00ffe1ec = DAT_00ffe1ec | 1 << (bVar2 & 0x1f);
    }
    uVar3 = (ushort)(byte)((pbVar1[1] - ('\f' - *pbVar1)) - 1);
    uVar5 = 0xc;
    DAT_00ffe1e8 = 0;
    do {
      DAT_00ffe1e8 = DAT_00ffe1e8 | 1 << (uVar5 & 0x1f);
      uVar5 = (uint)(byte)((char)uVar5 + 1);
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0xffff);
    sVar4 = (ushort)pbVar1[1] * 0x10 + -1;
    pbVar6 = pbVar1 + 2;
    puVar8 = (undefined4 *)((int)&DAT_00ffe780 + (int)(short)((ushort)*pbVar1 << 6));
    do {
      *puVar8 = *(undefined4 *)pbVar6;
      sVar4 = sVar4 + -1;
      pbVar6 = pbVar6 + 4;
      puVar8 = puVar8 + 1;
    } while (sVar4 != -1);
    if (DAT_00ffe1fa < 0xc) {
      pcVar7 = (char *)((int)&DAT_00ffe780 + (int)(short)(DAT_00ffe1fa << 6));
      sVar4 = 0xb - DAT_00ffe1fa;
      do {
        if (*pcVar7 != '\0') {
          sVar4 = FUN_00014c80();
          *(undefined2 *)(pcVar7 + 0x12) = *(undefined2 *)(pcVar7 + 0x1e);
        }
        pcVar7 = pcVar7 + 0x40;
        sVar4 = sVar4 + -1;
      } while (sVar4 != -1);
    }
    pcVar7 = &DAT_00ffea80;
    sVar4 = 0x11;
    do {
      if (*pcVar7 != '\0') {
        sVar4 = FUN_00014c80();
        *(undefined2 *)(pcVar7 + 0x12) = *(undefined2 *)(pcVar7 + 0x1e);
      }
      pcVar7 = pcVar7 + 0x40;
      sVar4 = sVar4 + -1;
    } while (sVar4 != -1);
  }
  return;
}

