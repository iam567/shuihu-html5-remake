/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000154f0 */

void FUN_000154f0(void)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  short sVar4;
  
  if ((DAT_00ff6004 & 0x40) == 0) {
    if ((DAT_00ff6004 & 0x10) != 0) {
      FUN_00027f18();
      FUN_00006912();
      FUN_00006928();
      FUN_00001098();
      FUN_00007c14();
      DAT_00ff605f = 0;
      DAT_00ff6085 = 1;
    }
  }
  else {
    FUN_00001098();
    DAT_00ffe1e0 = DAT_00ffe1e0 & ~(1 << (DAT_00ff606b & 0x1f));
    DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
    iVar3 = (int)(short)((ushort)DAT_00ff606b << 6);
    *(undefined1 *)((int)&DAT_00ffe780 + iVar3 + 1) = 4;
    *(undefined1 *)((int)&DAT_00ffe784 + iVar3 + 2) = 1;
    (&DAT_00ffe7ab)[(short)(ushort)DAT_00ff60b7 + iVar3] =
         (&DAT_00ffe7ab)[(short)(ushort)DAT_00ff60b7 + iVar3] + -1;
    pcVar2 = (char *)((int)&DAT_00ffe790 + iVar3 + 1);
    *pcVar2 = *pcVar2 + '\x01';
    if (99 < *(byte *)((int)&DAT_00ffe790 + iVar3 + 1)) {
      pcVar2 = (char *)((int)&DAT_00ffe790 + iVar3 + 1);
      *pcVar2 = *pcVar2 + -100;
      *(char *)((int)&DAT_00ffe790 + iVar3) = *(char *)((int)&DAT_00ffe790 + iVar3) + '\x01';
      DAT_00ff6150 = DAT_00ff606b;
      DAT_00ff614f = 1;
      iVar1 = *(int *)((int)&PTR_DAT_00005f24 +
                      (int)(short)((ushort)(byte)(&DAT_00ffe7a1)[iVar3] << 2));
      for (sVar4 = 1; *(char *)(iVar1 + sVar4) != 'd'; sVar4 = sVar4 + 2) {
        if (*(char *)((int)&DAT_00ffe790 + iVar3) == *(char *)(iVar1 + sVar4)) {
          (&DAT_00ffe7a4)[iVar3] = *(undefined1 *)(iVar1 + 1 + (int)sVar4);
          DAT_00ff614f = DAT_00ff614f | 2;
          break;
        }
      }
    }
    DAT_00ff6120 = 0;
    FUN_00016a28();
    DAT_00ff6085 = 0x11;
    FUN_0000c006();
    FUN_00027f58();
  }
  return;
}

