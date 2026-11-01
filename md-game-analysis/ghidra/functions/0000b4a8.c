/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000b4a8 */

void FUN_0000b4a8(void)

{
  ushort uVar1;
  int iVar2;
  char cVar3;
  ushort unaff_D2w;
  
  if (DAT_00ff605a == '\0') {
    iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
    DAT_00ff60ae = (*(short *)((int)&DAT_00ffe780 + iVar2 + 2) - DAT_00ff6014) + 0x80;
    DAT_00ff60b0 = (*(short *)((int)&DAT_00ffe784 + iVar2) - DAT_00ff6016) + 0x80;
    DAT_00ff60ad = 0xc;
    DAT_00ff6094 = *(undefined2 *)((int)&DAT_00ffe792 + iVar2);
    DAT_00ff6096 = *(undefined2 *)((int)&DAT_00ffe79e + iVar2);
    DAT_00ff609a = 0x60;
    cVar3 = FUN_0000a318();
    if (cVar3 == '\0') {
      (&DAT_00ffe79c)[iVar2] = 0x30;
      DAT_00ff60ae = DAT_00ff60ae + 8;
    }
    else {
      (&DAT_00ffe7a5)[iVar2] = 0x18;
      (&DAT_00ffe79d)[iVar2] = 4;
      DAT_00ff609d = 1;
      FUN_0000b58c();
      FUN_00005f9c();
      DAT_00ff6148 = 1;
      DAT_00ff6144 = *(undefined2 *)((int)&DAT_00ffe780 + iVar2 + 2);
      DAT_00ff6146 = *(undefined2 *)((int)&DAT_00ffe784 + iVar2);
      uVar1 = *(ushort *)((int)&DAT_00ffe792 + iVar2);
      DAT_00ff6142 = unaff_D2w;
      *(ushort *)((int)&DAT_00ffe792 + iVar2) = uVar1 - unaff_D2w;
      if (uVar1 < unaff_D2w) {
        *(undefined2 *)((int)&DAT_00ffe792 + iVar2) = 0;
      }
    }
    DAT_00ff6098 = *(undefined2 *)((int)&DAT_00ffe792 + iVar2);
    FUN_00027f38();
    DAT_00ff6085 = 10;
  }
  return;
}

