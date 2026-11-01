/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000a318 */

undefined1 FUN_0000a318(void)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  undefined1 uVar4;
  
  cVar1 = (&DAT_00ffe799)[(short)((ushort)DAT_00ff606b << 6)];
  cVar2 = (&DAT_00028e5a)
          [(short)((ushort)(byte)((&DAT_00ffe7a6)[(short)((ushort)DAT_00ff606b << 6)] - 1) << 3)];
  if (*(char *)((int)&DAT_00ffe78c + (int)(short)((ushort)DAT_00ff609f << 6)) == '\0') {
    bVar3 = (&DAT_00ffe79a)[(short)((ushort)DAT_00ff609f << 6)];
    if ((byte)(cVar2 + cVar1) < bVar3) {
      return 0;
    }
    uVar4 = FUN_0000604e();
    if ((byte)((cVar2 + cVar1) - bVar3) < (byte)((ushort)((DAT_00ff6100 & 0x3f) * 100) >> 6)) {
      return uVar4;
    }
  }
  return 1;
}

