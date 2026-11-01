/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00027950 */

void FUN_00027950(void)

{
  short sVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  ushort *puVar6;
  ushort *puVar7;
  
  if (DAT_00ff6119 != '\0') {
    if (DAT_00ff601a == '\a') {
      DAT_00ff6119 = '\0';
      DAT_00ff6044 = 1;
    }
    else if ((DAT_00ff601b & (byte)DAT_00ff6010) == 0) {
      sVar1 = 0xe;
      puVar5 = &DAT_00ffefa2;
      puVar6 = &DAT_00027a20;
      puVar7 = &DAT_00ffef22;
      do {
        uVar2 = *puVar5 & 0xe00;
        if (uVar2 != (*puVar6 & 0xe00)) {
          if (uVar2 < (*puVar6 & 0xe00)) {
            uVar2 = uVar2 + 0x200;
          }
          else {
            uVar2 = uVar2 - 0x200;
          }
        }
        uVar3 = *puVar5 & 0xe0;
        if (uVar3 != (*puVar6 & 0xe0)) {
          if (uVar3 < (*puVar6 & 0xe0)) {
            uVar3 = uVar3 + 0x20;
          }
          else {
            uVar3 = uVar3 - 0x20;
          }
        }
        uVar4 = *puVar5 & 0xe;
        if (uVar4 != (*puVar6 & 0xe)) {
          if (uVar4 < (*puVar6 & 0xe)) {
            uVar4 = uVar4 + 2;
          }
          else {
            uVar4 = uVar4 - 2;
          }
        }
        uVar4 = uVar4 | uVar3 | uVar2;
        *puVar5 = uVar4;
        *puVar7 = uVar4;
        sVar1 = sVar1 + -1;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      } while (sVar1 != -1);
      DAT_00ff601a = DAT_00ff601a + '\x01';
      DAT_00ff6001 = 0xff;
    }
  }
  return;
}

