/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00016ac6 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016ac6(void)

{
  uint extraout_D1;
  short sVar1;
  char unaff_D2b;
  short *psVar2;
  ushort *puVar3;
  short *psVar4;
  undefined6 uVar5;
  
  if (DAT_00ff6312 != '\0') {
    if ((DAT_00ff6311 & 3) == 0) {
      for (psVar4 = &DAT_00ff6330; *psVar4 != 0; psVar4 = psVar4 + 3) {
      }
      *psVar4 = 0x38;
      *(undefined4 *)(psVar4 + 1) = _DAT_00ff6328;
      psVar4[3] = 0x38;
      *(undefined4 *)(psVar4 + 4) = _DAT_00ff632c;
    }
    puVar3 = (ushort *)&DAT_00ff6320;
    psVar4 = &DAT_00ff6328;
    do {
      FUN_0001664e();
      sVar1 = (short)(((extraout_D1 & 0xffff) * (uint)*puVar3) / 10000);
      if (unaff_D2b != '\0') {
        sVar1 = -sVar1;
      }
      DAT_00ff6304 = DAT_00ff630c + sVar1;
      uVar5 = FUN_0001655c();
      sVar1 = (short)((((uint)uVar5 & 0xffff) * (uint)*puVar3) / 10000);
      if (unaff_D2b != '\0') {
        sVar1 = -sVar1;
      }
      DAT_00ff6306 = DAT_00ff630e + sVar1;
      psVar2 = psVar4 + 1;
      *psVar4 = DAT_00ff6304;
      psVar4 = psVar4 + 2;
      *psVar2 = DAT_00ff6306;
      puVar3 = puVar3 + 2;
    } while ((short)((uint6)uVar5 >> 0x20) != 0);
    DAT_00ff6311 = DAT_00ff6311 + 1;
    DAT_00ff6322 = DAT_00ff6322 + 8;
    DAT_00ff6326 = DAT_00ff6326 + 8;
    if (DAT_00ff6311 < 0x61) {
      DAT_00ff6320 = DAT_00ff6320 + 1;
      DAT_00ff6324 = DAT_00ff6324 + 1;
    }
    else if (DAT_00ff6311 < 0xc1) {
      DAT_00ff6320 = DAT_00ff6320 + -1;
      DAT_00ff6324 = DAT_00ff6324 + -1;
    }
    else {
      DAT_00ff6312 = '\0';
    }
  }
  return;
}

