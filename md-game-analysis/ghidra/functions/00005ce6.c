/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00005ce6 */

void FUN_00005ce6(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  byte bVar5;
  ushort unaff_D2w;
  short sVar6;
  undefined *puVar7;
  
  iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
  DAT_00ff60e8 = (int)&DAT_00ffe780 + iVar2;
  DAT_00ff6094 = *(undefined2 *)((int)&DAT_00ffe792 + iVar2);
  DAT_00ff6096 = *(undefined2 *)((int)&DAT_00ffe79e + iVar2);
  DAT_00ff614d = *(byte *)((int)&DAT_00ffe790 + iVar2);
  iVar2 = (int)(short)((ushort)DAT_00ff609f << 6);
  DAT_00ff614e = *(char *)((int)&DAT_00ffe790 + iVar2);
  DAT_00ff60ae = (*(short *)((int)&DAT_00ffe780 + iVar2 + 2) - DAT_00ff6014) + 0x80;
  DAT_00ff60b0 = (*(short *)((int)&DAT_00ffe784 + iVar2) - DAT_00ff6016) + 0x80;
  DAT_00ff60ad = 0xc;
  DAT_00ff608e = *(undefined2 *)((int)&DAT_00ffe792 + iVar2);
  DAT_00ff6090 = *(undefined2 *)((int)&DAT_00ffe79e + iVar2);
  DAT_00ff609a = 0x60;
  cVar4 = FUN_00005fdc();
  if (cVar4 == '\0') {
    (&DAT_00ffe79c)[iVar2] = 0x30;
    DAT_00ff60ae = DAT_00ff60ae + 8;
    DAT_00ff6092 = *(undefined2 *)((int)&DAT_00ffe792 + iVar2);
    DAT_00ff60a0 = 6;
    DAT_00ff60a2 = 0x10;
    DAT_00ff60a4 = 0x14;
    DAT_00ff60a6 = 0x10;
  }
  else {
    (&DAT_00ffe7a5)[iVar2] = 0x18;
    (&DAT_00ffe79d)[iVar2] = 4;
    if (DAT_00ff60bc == '\x11') {
      *(undefined1 *)((int)&DAT_00ffe78c + iVar2 + 1) = 1;
    }
    DAT_00ff609c = 1;
    FUN_00006070();
    FUN_00005f9c();
    DAT_00ff6148 = 1;
    DAT_00ff6144 = *(undefined2 *)((int)&DAT_00ffe780 + iVar2 + 2);
    DAT_00ff6146 = *(undefined2 *)((int)&DAT_00ffe784 + iVar2);
    puVar7 = &DAT_00005f08;
    uVar1 = *(ushort *)((int)&DAT_00ffe792 + iVar2);
    DAT_00ff6142 = unaff_D2w;
    *(ushort *)((int)&DAT_00ffe792 + iVar2) = uVar1 - unaff_D2w;
    if (uVar1 < unaff_D2w) {
      *(undefined2 *)((int)&DAT_00ffe792 + iVar2) = 0;
      puVar7 = &DAT_00005f16;
    }
    iVar3 = DAT_00ff60e8;
    DAT_00ff6092 = *(undefined2 *)((int)&DAT_00ffe792 + iVar2);
    DAT_00ff60a0 = 6;
    DAT_00ff60a2 = 0x10;
    DAT_00ff60a4 = 0x14;
    DAT_00ff60a6 = 0x10;
    bVar5 = (DAT_00ff614e + 5U) - DAT_00ff614d;
    if ((byte)(DAT_00ff614e + 5U) < DAT_00ff614d) {
      cVar4 = '\x01';
    }
    else {
      if (0xd < bVar5) {
        bVar5 = 0xd;
      }
      cVar4 = puVar7[(short)(ushort)bVar5];
    }
    *(char *)(DAT_00ff60e8 + 0x11) = cVar4 + *(char *)(DAT_00ff60e8 + 0x11);
    if (99 < *(byte *)(iVar3 + 0x11)) {
      *(char *)(iVar3 + 0x11) = *(char *)(iVar3 + 0x11) + -100;
      *(char *)(iVar3 + 0x10) = *(char *)(iVar3 + 0x10) + '\x01';
      DAT_00ff6150 = DAT_00ff606b;
      DAT_00ff614f = 1;
      iVar2 = *(int *)((int)&PTR_DAT_00005f24 + (int)(short)((ushort)*(byte *)(iVar3 + 0x21) << 2));
      for (sVar6 = 1; *(char *)(iVar2 + sVar6) != 'd'; sVar6 = sVar6 + 2) {
        if (*(char *)(iVar3 + 0x10) == *(char *)(iVar2 + sVar6)) {
          *(undefined1 *)(iVar3 + 0x24) = *(undefined1 *)(iVar2 + 1 + (int)sVar6);
          DAT_00ff614f = DAT_00ff614f | 2;
          break;
        }
      }
    }
  }
  Seed_e50();
  FUN_00027f38();
  return;
}

