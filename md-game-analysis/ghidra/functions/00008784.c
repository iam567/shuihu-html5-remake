/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00008784 */

void FUN_00008784(void)

{
  ushort uVar1;
  char *pcVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  byte bVar7;
  ushort unaff_D2w;
  short sVar8;
  undefined *puVar9;
  
  if (DAT_00ff605a == '\0') {
    iVar4 = (int)(short)((ushort)DAT_00ff606b << 6);
    DAT_00ff60ae = (*(short *)((int)&DAT_00ffe780 + iVar4 + 2) - DAT_00ff6014) + 0x80;
    DAT_00ff60b0 = (*(short *)((int)&DAT_00ffe784 + iVar4) - DAT_00ff6016) + 0x80;
    DAT_00ff60ad = 0xc;
    DAT_00ff608e = *(undefined2 *)((int)&DAT_00ffe792 + iVar4);
    DAT_00ff6090 = *(undefined2 *)((int)&DAT_00ffe79e + iVar4);
    DAT_00ff609a = 0x60;
    FUN_00027f38();
    cVar6 = FUN_00008940();
    if (cVar6 == '\0') {
      (&DAT_00ffe79c)[iVar4] = 0x30;
      DAT_00ff60ae = DAT_00ff60ae + 8;
      DAT_00ff6092 = *(undefined2 *)((int)&DAT_00ffe792 + iVar4);
      DAT_00ff6085 = 10;
    }
    else {
      (&DAT_00ffe7a5)[iVar4] = 0x18;
      (&DAT_00ffe79d)[iVar4] = 4;
      DAT_00ff609c = 1;
      FUN_000089b0();
      FUN_00005f9c();
      DAT_00ff6148 = 1;
      DAT_00ff6144 = *(undefined2 *)((int)&DAT_00ffe780 + iVar4 + 2);
      DAT_00ff6146 = *(undefined2 *)((int)&DAT_00ffe784 + iVar4);
      puVar9 = &DAT_00005f08;
      uVar1 = *(ushort *)((int)&DAT_00ffe792 + iVar4);
      DAT_00ff6142 = unaff_D2w;
      *(ushort *)((int)&DAT_00ffe792 + iVar4) = uVar1 - unaff_D2w;
      if (uVar1 < unaff_D2w) {
        *(undefined2 *)((int)&DAT_00ffe792 + iVar4) = 0;
        puVar9 = &DAT_00005f16;
      }
      DAT_00ff6092 = *(undefined2 *)((int)&DAT_00ffe792 + iVar4);
      DAT_00ff6085 = 10;
      if ((DAT_00ffe1ec == 0) || ((short)(ushort)DAT_00ff609f < DAT_00ffe1fa)) {
        iVar5 = (int)(short)((ushort)DAT_00ff609f << 6);
        bVar3 = *(char *)((int)&DAT_00ffe790 + iVar4) + 5;
        bVar7 = bVar3 - *(byte *)((int)&DAT_00ffe790 + iVar5);
        if (bVar3 < *(byte *)((int)&DAT_00ffe790 + iVar5)) {
          cVar6 = '\x01';
        }
        else {
          if (0xd < bVar7) {
            bVar7 = 0xd;
          }
          cVar6 = puVar9[(short)(ushort)bVar7];
        }
        pcVar2 = (char *)((int)&DAT_00ffe790 + iVar5 + 1);
        *pcVar2 = cVar6 + *pcVar2;
        if (99 < *(byte *)((int)&DAT_00ffe790 + iVar5 + 1)) {
          pcVar2 = (char *)((int)&DAT_00ffe790 + iVar5 + 1);
          *pcVar2 = *pcVar2 + -100;
          *(char *)((int)&DAT_00ffe790 + iVar5) = *(char *)((int)&DAT_00ffe790 + iVar5) + '\x01';
          DAT_00ff6150 = DAT_00ff609f;
          DAT_00ff614f = 1;
          iVar4 = *(int *)((int)&PTR_DAT_00005f24 +
                          (int)(short)((ushort)(byte)(&DAT_00ffe7a1)[iVar5] << 2));
          for (sVar8 = 1; *(char *)(iVar4 + sVar8) != 'd'; sVar8 = sVar8 + 2) {
            if (*(char *)((int)&DAT_00ffe790 + iVar5) == *(char *)(iVar4 + sVar8)) {
              (&DAT_00ffe7a4)[iVar5] = *(undefined1 *)(iVar4 + 1 + (int)sVar8);
              DAT_00ff614f = DAT_00ff614f | 2;
              return;
            }
          }
        }
      }
    }
  }
  return;
}

