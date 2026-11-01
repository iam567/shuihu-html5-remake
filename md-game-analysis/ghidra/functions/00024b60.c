/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00024b60 */

void FUN_00024b60(void)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  char cVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  
  iVar1 = *(int *)((int)&PTR_DAT_00024a08 + (int)(short)((ushort)DAT_00ffe10f << 2));
  pcVar5 = *(char **)(&DAT_00024962 + (short)((ushort)DAT_00ffe10f << 2));
  pcVar6 = (char *)&DAT_00ffe780;
  uVar2 = (ushort)(byte)(DAT_00ff6175 - 1);
  do {
    cVar4 = *pcVar6;
    if (cVar4 == '\x15') {
      cVar4 = '\x01';
    }
    sVar3 = 0;
    pcVar7 = pcVar5;
    while( true ) {
      if (*pcVar7 == -1) break;
      if (cVar4 == *pcVar7) {
        *(undefined4 *)(pcVar6 + 2) = *(undefined4 *)(iVar1 + (short)(sVar3 << 2));
        break;
      }
      sVar3 = sVar3 + 1;
      pcVar7 = pcVar7 + 1;
    }
    pcVar6 = pcVar6 + 0x40;
    uVar2 = uVar2 - 1;
    if (uVar2 == 0xffff) {
      pcVar5 = (char *)&DAT_00ffe780;
      sVar3 = 0xb;
      do {
        if (*pcVar5 == '\0') {
          return;
        }
        if (*(int *)(pcVar5 + 2) == 0) {
          FUN_000142a8(sVar3);
          sVar3 = FUN_00024c1a();
          *(undefined2 *)(pcVar5 + 2) = DAT_00ff613a;
          *(undefined2 *)(pcVar5 + 4) = DAT_00ff613c;
        }
        pcVar5 = pcVar5 + 0x40;
        sVar3 = sVar3 + -1;
      } while (sVar3 != -1);
      return;
    }
  } while( true );
}

