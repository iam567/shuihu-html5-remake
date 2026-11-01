/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00014ff2 */

void FUN_00014ff2(void)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  byte bVar4;
  short sVar5;
  char cVar6;
  int unaff_A2;
  
  iVar3 = (int)(short)((ushort)DAT_00ff606b << 6);
  bVar4 = *(byte *)(unaff_A2 + 0x10) - *(byte *)((int)&DAT_00ffe790 + iVar3);
  if (*(byte *)(unaff_A2 + 0x10) < *(byte *)((int)&DAT_00ffe790 + iVar3)) {
    cVar6 = '\x01';
  }
  else {
    if (8 < bVar4) {
      bVar4 = 8;
    }
    cVar6 = (&DAT_00005f08)[(short)(ushort)bVar4];
  }
  pcVar2 = (char *)((int)&DAT_00ffe790 + iVar3 + 1);
  *pcVar2 = cVar6 + *pcVar2;
  if (99 < *(byte *)((int)&DAT_00ffe790 + iVar3 + 1)) {
    pcVar2 = (char *)((int)&DAT_00ffe790 + iVar3 + 1);
    *pcVar2 = *pcVar2 + -100;
    *(char *)((int)&DAT_00ffe790 + iVar3) = *(char *)((int)&DAT_00ffe790 + iVar3) + '\x01';
    DAT_00ff6150 = DAT_00ff606b;
    DAT_00ff614f = 1;
    iVar1 = *(int *)((int)&PTR_DAT_00005f24 +
                    (int)(short)((ushort)(byte)(&DAT_00ffe7a1)[iVar3] << 2));
    for (sVar5 = 1; *(char *)(iVar1 + sVar5) != 'd'; sVar5 = sVar5 + 2) {
      if (*(char *)((int)&DAT_00ffe790 + iVar3) == *(char *)(iVar1 + sVar5)) {
        (&DAT_00ffe7a4)[iVar3] = *(undefined1 *)(iVar1 + 1 + (int)sVar5);
        DAT_00ff614f = DAT_00ff614f | 2;
        return;
      }
    }
  }
  return;
}

