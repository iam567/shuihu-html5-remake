/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00016316 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016316(void)

{
  ushort uVar1;
  short sVar2;
  undefined2 unaff_D3w;
  undefined2 unaff_D4w;
  undefined4 *unaff_A2;
  byte *pbVar3;
  char *pcVar4;
  
  if (DAT_00ff614a != '\0') {
    for (pcVar4 = &DAT_00ff5100; *pcVar4 != '\0'; pcVar4 = pcVar4 + 6) {
    }
    uVar1 = (ushort)(byte)(DAT_00ff614b - 1);
    do {
      if (DAT_00ff614a == '\x01') {
        *unaff_A2 = _DAT_00ff6048;
      }
      else {
        FUN_0001646a();
        uVar1 = FUN_000162b4();
        *(undefined2 *)unaff_A2 = unaff_D3w;
        *(undefined2 *)((int)unaff_A2 + 2) = unaff_D4w;
      }
      *(undefined2 *)(unaff_A2 + 1) = 0x49;
      unaff_A2 = (undefined4 *)((int)unaff_A2 + 6);
      DAT_00ff6012 = DAT_00ff6012 + 1;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0xffff);
    DAT_00ff614a = DAT_00ff614a + '\x01';
    if (DAT_00ff614a == '\"') {
      DAT_00ff614a = '\0';
      FUN_00027f98();
      DAT_00ff6155 = 1;
      DAT_00ff6103 = 2;
      FUN_00009c4a();
      FUN_00001098();
      FUN_000163ee();
      pbVar3 = &DAT_00ff7180;
      while( true ) {
        if (*pbVar3 == 0xff) break;
        sVar2 = (ushort)*pbVar3 << 6;
        (&DAT_00ffe79d)[sVar2] = 4;
        (&DAT_00ffe7a5)[sVar2] = 0x18;
        pbVar3 = pbVar3 + 1;
      }
    }
  }
  return;
}

