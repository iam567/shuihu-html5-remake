/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007c62 */

void FUN_00007c62(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  ushort uVar4;
  short sVar5;
  short *unaff_A2;
  
  iVar3 = (int)(short)((ushort)DAT_00ff606b << 6);
  if (*(char *)((int)&DAT_00ffe780 + iVar3) != '\0') {
    uVar4 = (ushort)DAT_00ff606b;
    sVar2 = *(short *)((int)&DAT_00ffe780 + iVar3 + 2) - DAT_00ff6014;
    sVar5 = sVar2 + 0x80;
    if ((((0x60 < sVar5) && (sVar5 < 0x1c0)) &&
        (sVar1 = (*(short *)((int)&DAT_00ffe784 + iVar3) - DAT_00ff6016) + 0x80, 0x60 < sVar1)) &&
       (sVar1 < 0x160)) {
      if ((&DAT_00ffe7a5)[iVar3] == '\0') {
        if ((&DAT_00ffe79c)[iVar3] != '\0') {
          (&DAT_00ffe79c)[iVar3] = (&DAT_00ffe79c)[iVar3] + -1;
          sVar5 = sVar2 + 0x78;
        }
      }
      else {
        (&DAT_00ffe7a5)[iVar3] = (&DAT_00ffe7a5)[iVar3] + -1;
        sVar5 = *(short *)(&DAT_00002300 + (short)((ushort)(byte)(&DAT_00ffe7a5)[iVar3] << 1)) +
                sVar5;
      }
      *unaff_A2 = sVar5;
      unaff_A2[1] = sVar1;
      uVar4 = *(ushort *)
               (&DAT_00002330 +
               (int)(short)((ushort)*(byte *)((int)&DAT_00ffe780 + iVar3 + 1) << 1) +
               (int)(short)(uVar4 << 5) + (int)(short)(uVar4 << 2));
      if (((&DAT_00ffe79d)[iVar3] != '\0') && (uVar4 = uVar4 | 0x6000, (&DAT_00ffe79d)[iVar3] != -1)
         ) {
        (&DAT_00ffe79d)[iVar3] = (&DAT_00ffe79d)[iVar3] + -1;
      }
      unaff_A2[2] = uVar4;
      DAT_00ff6012 = DAT_00ff6012 + 1;
    }
  }
  return;
}

