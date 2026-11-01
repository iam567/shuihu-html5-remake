/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003f30 */

undefined8 FUN_00003f30(void)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar5;
  uint uVar6;
  int unaff_A2;
  short *unaff_A3;
  byte *unaff_A5;
  
  bVar2 = unaff_A5[2];
  if ((bVar2 & 1) == 0) {
    if (*(short *)(unaff_A2 + 2) != *unaff_A3) {
      bVar1 = *unaff_A5;
      uVar5 = (ushort)bVar1;
      if ((char)bVar1 < '\0') {
        uVar5 = -(ushort)(byte)-bVar1;
      }
      *(short *)(unaff_A2 + 2) = uVar5 + *(short *)(unaff_A2 + 2);
    }
    if (*(short *)(unaff_A2 + 4) != unaff_A3[1]) {
      uVar3 = (ushort)((ushort)unaff_A5[1] + (ushort)unaff_A5[3]) / 100;
      uVar4 = (uint)(ushort)((ushort)unaff_A5[1] + (ushort)unaff_A5[3]) % 100;
      uVar6 = uVar4 << 0x10 | uVar3;
      if ((bVar2 & 0x80) != 0) {
        uVar6 = CONCAT22((short)uVar4,-(short)uVar3);
      }
      *(short *)(unaff_A2 + 4) = (short)uVar6 + *(short *)(unaff_A2 + 4);
      unaff_A5[3] = (byte)(uVar6 >> 0x10);
    }
  }
  else {
    if (*(short *)(unaff_A2 + 4) != unaff_A3[1]) {
      bVar1 = unaff_A5[1];
      uVar5 = (ushort)bVar1;
      if ((char)bVar1 < '\0') {
        uVar5 = -(ushort)(byte)-bVar1;
      }
      *(short *)(unaff_A2 + 4) = uVar5 + *(short *)(unaff_A2 + 4);
    }
    if (*(short *)(unaff_A2 + 2) != *unaff_A3) {
      uVar3 = (ushort)((ushort)*unaff_A5 + (ushort)unaff_A5[3]) / 100;
      uVar4 = (uint)(ushort)((ushort)*unaff_A5 + (ushort)unaff_A5[3]) % 100;
      uVar6 = uVar4 << 0x10 | uVar3;
      if ((bVar2 & 0x80) != 0) {
        uVar6 = CONCAT22((short)uVar4,-(short)uVar3);
      }
      *(short *)(unaff_A2 + 2) = (short)uVar6 + *(short *)(unaff_A2 + 2);
      unaff_A5[3] = (byte)(uVar6 >> 0x10);
    }
  }
  return CONCAT44(in_D0,in_D1);
}

