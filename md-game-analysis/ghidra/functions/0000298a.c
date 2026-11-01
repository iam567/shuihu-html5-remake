/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000298a */

void FUN_0000298a(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  ushort *puVar7;
  ushort *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  
  if ((DAT_00ff6019 & 2) != 0) {
    if (DAT_00ff601a == '\a') {
      DAT_00ff6019 = DAT_00ff6019 & 0xfd;
      DAT_00ff603d = DAT_00ff603d | 2;
    }
    else if ((DAT_00ff601b & (byte)DAT_00ff6010) == 0) {
      puVar7 = &DAT_00ffef00;
      puVar9 = &DAT_00ffef80;
      uVar6 = 0;
      sVar1 = 3;
      do {
        if ((DAT_00ff601c & '\x01' << (uVar6 & 7)) == 0) {
          puVar7 = puVar7 + 0x10;
          puVar9 = puVar9 + 0x10;
        }
        else {
          sVar2 = 0xf;
          puVar8 = puVar7;
          puVar10 = puVar9;
          do {
            uVar3 = *puVar10 & 0xe00;
            if (uVar3 < (*puVar8 & 0xe00)) {
              uVar3 = uVar3 + 0x200;
            }
            uVar4 = *puVar10 & 0xe0;
            if (uVar4 < (*puVar8 & 0xe0)) {
              uVar4 = uVar4 + 0x20;
            }
            puVar7 = puVar8 + 1;
            uVar5 = *puVar10 & 0xe;
            if (uVar5 < (*puVar8 & 0xe)) {
              uVar5 = uVar5 + 2;
            }
            puVar9 = puVar10 + 1;
            *puVar10 = uVar5 | uVar4 | uVar3;
            sVar2 = sVar2 + -1;
            puVar8 = puVar7;
            puVar10 = puVar9;
          } while (sVar2 != -1);
        }
        uVar6 = (uint)(ushort)((short)uVar6 + 1);
        sVar1 = sVar1 + -1;
      } while (sVar1 != -1);
      DAT_00ff601a = DAT_00ff601a + '\x01';
      DAT_00ff6001 = 0xff;
    }
  }
  return;
}

