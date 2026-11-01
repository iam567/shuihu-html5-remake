/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000e8ba */

void FUN_0000e8ba(void)

{
  int iVar1;
  short unaff_D2w;
  
  iVar1 = (int)(short)((ushort)DAT_00ff60bd << 6);
  (&DAT_00ffe79d)[iVar1] = 0x60;
  DAT_00ff6094 = *(undefined2 *)((int)&DAT_00ffe792 + iVar1);
  DAT_00ff6096 = *(undefined2 *)((int)&DAT_00ffe79e + iVar1);
  DAT_00ff609a = 0x60;
  DAT_00ff609d = 1;
  FUN_0000a8a0();
  DAT_00ff6098 = unaff_D2w + *(short *)((int)&DAT_00ffe792 + iVar1);
  if (*(ushort *)((int)&DAT_00ffe79e + iVar1) < DAT_00ff6098) {
    DAT_00ff6098 = *(ushort *)((int)&DAT_00ffe79e + iVar1);
  }
  *(ushort *)((int)&DAT_00ffe792 + iVar1) = DAT_00ff6098;
  DAT_00ff60a4 = 0xd;
  DAT_00ff60a6 = 0x10;
  DAT_00ff60a0 = 0;
  DAT_00ff60a2 = 0x1c;
  Seed_e50();
  FUN_00009c4a();
  DAT_00ff60aa = 0xff;
  DAT_00ff60ab = 7;
  FUN_00027f48();
  return;
}

