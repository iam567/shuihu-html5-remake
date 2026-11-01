/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000028c2 */

void FUN_000028c2(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  ushort *puVar7;
  ushort *puVar8;
  
  if ((DAT_00ff6019 & 1) != 0) {
    if (DAT_00ff601a == '\a') {
      DAT_00ff6019 = DAT_00ff6019 & 0xfe;
      DAT_00ff603d = DAT_00ff603d | 2;
    }
    else if ((DAT_00ff601b & (byte)DAT_00ff6010) == 0) {
      uVar6 = 0;
      sVar1 = 3;
      puVar7 = &DAT_00ffef80;
      do {
        if ((DAT_00ff601c & '\x01' << (uVar6 & 7)) == 0) {
          puVar8 = puVar7 + 0x10;
        }
        else {
          if ((short)uVar6 == 0) {
            sVar2 = 0xe;
            puVar7 = puVar7 + 1;
          }
          else {
            sVar2 = 0xf;
          }
          do {
            uVar3 = *puVar7 & 0xe00;
            if (uVar3 != 0) {
              uVar3 = uVar3 - 0x200;
            }
            uVar4 = *puVar7 & 0xe0;
            if (uVar4 != 0) {
              uVar4 = uVar4 - 0x20;
            }
            uVar5 = *puVar7 & 0xe;
            if (uVar5 != 0) {
              uVar5 = uVar5 - 2;
            }
            puVar8 = puVar7 + 1;
            *puVar7 = uVar5 | uVar4 | uVar3;
            sVar2 = sVar2 + -1;
            puVar7 = puVar8;
          } while (sVar2 != -1);
        }
        uVar6 = (uint)(ushort)((short)uVar6 + 1);
        sVar1 = sVar1 + -1;
        puVar7 = puVar8;
      } while (sVar1 != -1);
      DAT_00ff601a = DAT_00ff601a + '\x01';
      DAT_00ff6001 = 0xff;
    }
  }
  return;
}

