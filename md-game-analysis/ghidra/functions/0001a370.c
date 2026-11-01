/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001a370 */

void FUN_0001a370(void)

{
  int iVar1;
  short sVar2;
  char *pcVar3;
  
  DAT_00ff6037 = DAT_00ff6037 & 0xfe;
  iVar1 = (int)(short)((ushort)(byte)((&DAT_00ffe610)[(short)(ushort)DAT_00ff615b] - 1) << 4);
  if (DAT_00ff6177 == '\x02') {
    pcVar3 = &DAT_00ffe639 + iVar1;
    if (*pcVar3 == '\0') {
LAB_0001a3de:
      DAT_00ff6037 = DAT_00ff6037 | 1;
      DAT_00ff60e8 = pcVar3;
    }
  }
  else {
    sVar2 = 3;
    if (DAT_00ff6177 == '\0') {
      pcVar3 = (char *)((int)&DAT_00ffe63a + iVar1);
    }
    else {
      pcVar3 = (char *)((int)&DAT_00ffe632 + iVar1);
    }
    do {
      if (*pcVar3 == '\0') goto LAB_0001a3de;
      pcVar3 = pcVar3 + 1;
      sVar2 = sVar2 + -1;
    } while (sVar2 != -1);
  }
  return;
}

