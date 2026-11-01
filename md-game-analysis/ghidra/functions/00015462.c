/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00015462 */

void FUN_00015462(void)

{
  short sVar1;
  char cVar2;
  int iVar3;
  ushort uVar4;
  byte *pbVar5;
  char *pcVar6;
  
  pcVar6 = &DAT_00ff71a0;
  pbVar5 = &DAT_00ff7180;
  while (*pbVar5 != 0xff) {
    iVar3 = (int)(short)((ushort)*pbVar5 << 6);
    cVar2 = (char)(*(ushort *)((int)&DAT_00ffe784 + iVar3) >> 5) - DAT_00ffe105;
    *pcVar6 = ((char)(*(ushort *)((int)&DAT_00ffe780 + iVar3 + 2) >> 5) - DAT_00ffe104) * '\x04' +
              '\x03';
    pcVar6[1] = cVar2 * '\x04' + '\x02';
    sVar1 = *(short *)((int)&DAT_00ffe792 + iVar3);
    *(short *)(pcVar6 + 2) = sVar1;
    uVar4 = DAT_00ff6152 + sVar1;
    if (*(ushort *)((int)&DAT_00ffe79e + iVar3) < uVar4) {
      uVar4 = *(ushort *)((int)&DAT_00ffe79e + iVar3);
    }
    *(ushort *)(pcVar6 + 6) = uVar4;
    *(ushort *)((int)&DAT_00ffe792 + iVar3) = uVar4;
    (&DAT_00ffe79d)[iVar3] = 0x60;
    uVar4 = (ushort)(uVar4 - *(short *)(pcVar6 + 2)) >> 5;
    if (uVar4 == 0) {
      uVar4 = 1;
    }
    *(ushort *)(pcVar6 + 4) = uVar4;
    pcVar6 = pcVar6 + 8;
    pbVar5 = pbVar5 + 1;
  }
  builtin_strncpy(pcVar6,"\x124Vx",4);
  return;
}

