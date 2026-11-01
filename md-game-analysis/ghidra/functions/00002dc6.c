/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00002dc6 */

void FUN_00002dc6(void)

{
  byte bVar1;
  ushort uVar2;
  byte bVar3;
  char unaff_D7b;
  byte *unaff_A2;
  byte *pbVar4;
  byte *pbVar5;
  byte *unaff_A3;
  
  do {
    while( true ) {
      while( true ) {
        while( true ) {
          pbVar4 = unaff_A2 + 1;
          bVar3 = *unaff_A2;
          if (bVar3 != 0xf0) break;
          unaff_D7b = '\0';
          unaff_A2 = pbVar4;
        }
        if (bVar3 != 0xf1) break;
        unaff_D7b = '\x01';
        unaff_A2 = pbVar4;
      }
      if (0xef < bVar3) break;
      *unaff_A3 = bVar3;
      unaff_A2 = pbVar4;
      unaff_A3 = unaff_A3 + 1;
    }
    if (bVar3 == 0xff) {
      pbVar5 = unaff_A2 + 2;
      bVar3 = *pbVar4;
      if (bVar3 == 0) {
        return;
      }
    }
    else {
      bVar3 = bVar3 & 0xf;
      pbVar5 = pbVar4;
    }
    if (unaff_D7b == '\0') {
      uVar2 = (ushort)(byte)(bVar3 - 1);
      unaff_A2 = pbVar5 + 1;
      bVar3 = *pbVar5;
      pbVar4 = unaff_A3;
      do {
        unaff_A3 = pbVar4 + 1;
        *pbVar4 = bVar3;
        uVar2 = uVar2 - 1;
        pbVar4 = unaff_A3;
      } while (uVar2 != 0xffff);
    }
    else {
      uVar2 = (ushort)(byte)(bVar3 - 1);
      bVar3 = *pbVar5;
      unaff_A2 = pbVar5 + 2;
      bVar1 = pbVar5[1];
      do {
        pbVar4 = unaff_A3 + 1;
        *unaff_A3 = bVar3;
        unaff_A3 = unaff_A3 + 2;
        *pbVar4 = bVar1;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0xffff);
    }
  } while( true );
}

