/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e7642 */

undefined8 FUN_001e7642(void)

{
  ushort uVar1;
  byte bVar2;
  short sVar3;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar4;
  byte bVar5;
  
  sVar3 = (short)in_D0 << 2;
  uVar1 = *(ushort *)(&DAT_001d84b6 + sVar3);
  if ((short)uVar1 < 0) {
    DAT_00a00022 = (&DAT_001d84b8)[sVar3];
    DAT_00a00020 = (&DAT_001d84b7)[sVar3];
  }
  else {
    bVar2 = (byte)(uVar1 >> 8) & 0xf;
    uVar4 = (uVar1 >> 8 & 0xfff0) >> 3;
    bVar5 = (&DAT_00ff6f54)[(short)uVar4] & 0xf;
    if (((&DAT_00ff6f54)[(short)uVar4] & 8) == 0) {
      if ((char)(bVar2 - bVar5) < '\0') goto LAB_001e76a0;
    }
    else if (bVar2 <= bVar5) goto LAB_001e76a0;
    *(ushort *)(&DAT_00ff6f54 + (short)uVar4) = uVar1;
  }
LAB_001e76a0:
  return CONCAT44(in_D0,in_D1);
}

