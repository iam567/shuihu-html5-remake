/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00009334 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00009334(void)

{
  short sVar1;
  char *pcVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  ushort uVar6;
  ushort unaff_D3w;
  byte bVar7;
  short *psVar8;
  short *psVar10;
  short *psVar9;
  
  DAT_00ff605c = CONCAT11(DAT_00ff6062,DAT_00ff6063);
  FUN_00006902();
  bVar5 = DAT_00ffe107;
  bVar4 = DAT_00ffe106;
  bVar7 = *(byte *)((int)&DAT_00ffb000 + (int)(short)unaff_D3w);
  uVar6 = (ushort)DAT_00ffe106;
  psVar10 = &DAT_00ff9002;
  _DAT_00ff9000 = 0xffff;
  DAT_00ff9002 = DAT_00ff605c;
  DAT_00ff6066 = DAT_00ff605c;
  while (psVar10 = psVar10 + 1, DAT_00ff605c != 0) {
    if (((uVar6 <= unaff_D3w) &&
        (bVar3 = *(byte *)((int)&DAT_00ffb000 + (int)(short)(unaff_D3w - uVar6)), bVar3 < 0x7f)) &&
       (bVar7 < bVar3)) {
      DAT_00ff6066 = DAT_00ff605c + -1;
      bVar7 = bVar3;
      DAT_00ff6068 = unaff_D3w - uVar6;
    }
    if ((byte)DAT_00ff605c < bVar5) {
      bVar3 = *(byte *)((int)&DAT_00ffb000 + (int)(short)(uVar6 + unaff_D3w));
      if ((bVar3 < 0x7f) && (bVar7 < bVar3)) {
        DAT_00ff6066 = DAT_00ff605c + 1;
        bVar7 = bVar3;
        DAT_00ff6068 = uVar6 + unaff_D3w;
      }
    }
    if (DAT_00ff605c._0_1_ != 0) {
      bVar3 = *(byte *)((int)&DAT_00ffb000 + (int)(short)(unaff_D3w - 1));
      if ((bVar3 < 0x7f) && (bVar7 < bVar3)) {
        DAT_00ff6066 = DAT_00ff605c + -0x100;
        bVar7 = bVar3;
        DAT_00ff6068 = unaff_D3w - 1;
      }
    }
    if (DAT_00ff605c._0_1_ < bVar4) {
      bVar3 = *(byte *)((int)&DAT_00ffb000 + (int)(short)(unaff_D3w + 1));
      if ((bVar3 < 0x7f) && (bVar7 < bVar3)) {
        DAT_00ff6066 = DAT_00ff605c + 0x100;
        bVar7 = bVar3;
        DAT_00ff6068 = unaff_D3w + 1;
      }
    }
    unaff_D3w = DAT_00ff6068;
    if (DAT_00ff6066 == DAT_00ff605c) break;
    DAT_00ff605c = DAT_00ff6066;
    *psVar10 = DAT_00ff6066;
  }
  psVar8 = &DAT_00ffa000;
  while( true ) {
    psVar10 = psVar10 + -1;
    if (*psVar10 == -1) break;
    *psVar8 = *psVar10;
    psVar8 = psVar8 + 1;
  }
  *psVar8 = -1;
  psVar10 = &DAT_00ffa000;
  DAT_00ff6037 = 0;
  if (DAT_00ffa002 != -1) {
    psVar8 = &DAT_00ffa002;
    if ((char)DAT_00ffa000 != (char)DAT_00ffa002) {
      DAT_00ff6037 = 1;
    }
    while( true ) {
      psVar9 = psVar8 + 1;
      sVar1 = *psVar8;
      if (sVar1 == -1) break;
      *psVar10 = sVar1;
      if ((DAT_00ff6037 & 1) == 0) {
        pcVar2 = (char *)((int)psVar8 + 3);
        psVar8 = psVar9;
        if ((char)sVar1 != *pcVar2) {
          DAT_00ff6037 = DAT_00ff6037 ^ 1;
          psVar10 = psVar10 + 1;
        }
      }
      else {
        psVar8 = psVar9;
        if ((char)((ushort)sVar1 >> 8) != *(char *)psVar9) {
          DAT_00ff6037 = DAT_00ff6037 ^ 1;
          psVar10 = psVar10 + 1;
        }
      }
    }
    *psVar10 = -1;
  }
  return;
}

