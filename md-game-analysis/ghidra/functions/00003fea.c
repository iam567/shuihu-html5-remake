/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003fea */

undefined8 FUN_00003fea(void)

{
  undefined4 in_D0;
  short sVar1;
  ushort uVar2;
  uint in_D1;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  undefined **ppuVar6;
  
  pcVar5 = &DAT_00ffe000;
  uVar4 = 0;
  sVar1 = 0xf;
  uVar3 = in_D1;
  do {
    if (*pcVar5 != '\0') {
      ppuVar6 = &PTR_DAT_00004086;
      uVar2 = (ushort)(uVar3 >> 0x10);
      if ((CONCAT22(uVar2,DAT_00ff6040) & 1 << (uVar4 & 0x1f)) != 0) {
        ppuVar6 = (undefined **)&DAT_0000408e;
      }
      uVar3 = CONCAT31((int3)(((uint)uVar2 << 0x10) >> 8),pcVar5[6]);
      if ((byte)pcVar5[6] < 8) {
        pcVar5[1] = *(char *)((int)ppuVar6 + (int)(short)uVar3);
        DAT_00ff601e = DAT_00ff601e | (ushort)(1 << (uVar4 & 0x1f));
        uVar3 = CONCAT22(uVar2,DAT_00ff603e >> 2);
        if (((DAT_00ffe10d != '\x04') &&
            (uVar3 = CONCAT22(uVar2,DAT_00ff603e >> 3), DAT_00ffe10d != '\x02')) &&
           (uVar3 = CONCAT22(uVar2,DAT_00ff603e >> 4), DAT_00ffe10d != '\x01')) {
          uVar3 = CONCAT22(uVar2,DAT_00ff603e >> 5);
        }
        uVar3 = uVar3 & 0xffffff03;
        pcVar5[1] = (char)uVar3 + pcVar5[1];
      }
    }
    pcVar5 = pcVar5 + 0x10;
    uVar4 = (uint)(byte)((char)uVar4 + 1);
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return CONCAT44(in_D0,in_D1);
}

