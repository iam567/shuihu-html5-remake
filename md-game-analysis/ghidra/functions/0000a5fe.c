/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000a5fe */

void FUN_0000a5fe(void)

{
  int iVar1;
  
  iVar1 = (int)(short)((ushort)(byte)(&DAT_00ff7180)[(short)(ushort)DAT_00ff6087] << 6);
  (&DAT_00ffe79d)[iVar1] = 0x60;
  DAT_00ff6094 = *(undefined2 *)((int)&DAT_00ffe792 + iVar1);
  DAT_00ff6096 = *(short *)((int)&DAT_00ffe79e + iVar1);
  DAT_00ff609a = 0x60;
  DAT_00ff609d = 1;
  DAT_00ff6152 = 0x19;
  if ((((DAT_00ff60bc != -0x7b) && (DAT_00ff6152 = 0x4b, DAT_00ff60bc != -0x7a)) &&
      (DAT_00ff6152 = 0x32, DAT_00ff60bc != '`')) &&
     (((DAT_00ff60bc != -0x80 && (DAT_00ff6152 = 100, DAT_00ff60bc != 'a')) &&
      (DAT_00ff60bc != -0x7f)))) {
    DAT_00ff6152 = DAT_00ff6096;
  }
  DAT_00ff6098 = DAT_00ff6152 + *(short *)((int)&DAT_00ffe792 + iVar1);
  if (*(ushort *)((int)&DAT_00ffe79e + iVar1) < DAT_00ff6098) {
    DAT_00ff6098 = *(ushort *)((int)&DAT_00ffe79e + iVar1);
  }
  *(ushort *)((int)&DAT_00ffe792 + iVar1) = DAT_00ff6098;
  FUN_00014ff2();
  DAT_00ff60a0 = 0;
  DAT_00ff60a2 = 0x1c;
  DAT_00ff60a4 = 0xd;
  DAT_00ff60a6 = 0x10;
  Seed_e50();
  FUN_00009c4a();
  DAT_00ff60aa = 0xff;
  DAT_00ff60ab = 7;
  FUN_00027f48();
  return;
}

