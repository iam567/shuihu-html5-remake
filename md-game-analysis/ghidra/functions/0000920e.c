/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000920e */

undefined6 FUN_0000920e(void)

{
  byte bVar1;
  undefined4 in_D1;
  short sVar2;
  ushort uVar3;
  ushort uVar4;
  short sVar5;
  byte *unaff_A4;
  
  sVar2 = (ushort)DAT_00ff606b << 6;
  bVar1 = (&DAT_00ffe794)[sVar2];
  sVar5 = (ushort)(byte)((&DAT_00ffe7a6)[sVar2] - 1) << 3;
  if (*(char *)((int)&PTR_DAT_00028e5b + (int)sVar5) != '\0') {
    bVar1 = (&DAT_00ffe795)[sVar2];
  }
  uVar3 = (ushort)(byte)(&DAT_00028e54)[sVar5] + (ushort)bVar1;
  bVar1 = *(byte *)((int)&PTR_DAT_0000611e +
                   (int)(short)(ushort)(&DAT_00ffe7a1)[(short)((ushort)*unaff_A4 << 6)] +
                   (int)(short)((ushort)DAT_00ffe7a1 * 0xf));
  if (bVar1 != 0) {
    uVar3 = (ushort)(((uint)uVar3 * (uint)bVar1) / 10);
  }
  sVar2 = (ushort)*unaff_A4 << 6;
  bVar1 = (&DAT_00ffe796)[sVar2];
  if (*(char *)((int)&PTR_DAT_00028e5b + (int)sVar5) != '\0') {
    bVar1 = (&DAT_00ffe797)[sVar2];
  }
  uVar4 = uVar3 - bVar1;
  if (uVar3 < bVar1) {
    uVar4 = 0;
  }
  sVar5 = 0;
  if (*(ushort *)((int)&DAT_00ffe792 + (int)sVar2) < uVar4) {
    sVar5 = 10;
  }
  return CONCAT24((short)(((uint)uVar4 * 10) / (uint)*(ushort *)((int)&DAT_00ffe79e + (int)sVar2)) *
                  2 + sVar5,in_D1);
}

