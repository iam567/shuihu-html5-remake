/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001683e */

void FUN_0001683e(void)

{
  short sVar1;
  uint extraout_D1;
  ushort uVar2;
  char unaff_D2b;
  short *psVar3;
  short *psVar4;
  ushort *puVar5;
  ushort *puVar6;
  ushort *puVar7;
  undefined6 uVar8;
  
  if (DAT_00ff6310 != '\0') {
    puVar7 = &DAT_00ff6320;
    psVar3 = &DAT_00ff6380;
    do {
      FUN_0001664e();
      sVar1 = (short)(((extraout_D1 & 0xffff) * (uint)(*puVar7 >> 4)) / 10000);
      if (unaff_D2b != '\0') {
        sVar1 = -sVar1;
      }
      DAT_00ff6304 = DAT_00ff630c + sVar1;
      uVar8 = FUN_0001655c();
      sVar1 = (short)((((uint)uVar8 & 0xffff) * (uint)(puVar7[1] >> 4)) / 10000);
      if (unaff_D2b != '\0') {
        sVar1 = -sVar1;
      }
      DAT_00ff6306 = puVar7[3] + DAT_00ff630e + sVar1;
      psVar4 = psVar3 + 1;
      *psVar3 = DAT_00ff6304;
      psVar3 = psVar3 + 2;
      *psVar4 = DAT_00ff6306;
      puVar7 = puVar7 + 4;
    } while ((short)((uint6)uVar8 >> 0x20) != 0);
    puVar7 = &DAT_000169c8;
    puVar5 = &DAT_00ff6320;
    sVar1 = 0xb;
    do {
      if (DAT_00ff6301 < 9) {
        *puVar5 = *puVar7 + *puVar5;
        puVar5[1] = puVar7[1] + puVar5[1];
        puVar5[2] = puVar7[2] + puVar5[2];
      }
      else {
        uVar2 = *puVar7 >> 3;
        if (*puVar5 == *puVar7) {
          uVar2 = 0;
        }
        puVar6 = puVar5 + 1;
        *puVar5 = *puVar5 - uVar2;
        uVar2 = puVar7[1] >> 3;
        if (*puVar6 == puVar7[1]) {
          uVar2 = 0;
        }
        *puVar6 = *puVar6 - uVar2;
        puVar5[2] = puVar7[2] * 4 + puVar5[2];
        puVar5[3] = puVar5[3] - puVar7[3];
      }
      puVar5 = puVar5 + 4;
      puVar7 = puVar7 + 4;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    DAT_00ff6301 = DAT_00ff6301 + 1;
    if (0x70 < DAT_00ff6301) {
      DAT_00ff6310 = '\0';
      DAT_00ff6300 = DAT_00ff6300 & 0xfe;
      DAT_00ff603d = DAT_00ff603d | 2;
    }
  }
  return;
}

