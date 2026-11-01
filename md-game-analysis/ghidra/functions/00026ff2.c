/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00026ff2 */

/* WARNING: This function may have set the stack pointer */

void FUN_00026ff2(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  int unaff_A6;
  
  FUN_00000ef0();
  if ((((*(char *)(unaff_A6 + 1) == '\x06') && (*(char *)(unaff_A6 + 3) == '\t')) &&
      (*(char *)(unaff_A6 + 5) == '\x01')) && (*(char *)(unaff_A6 + 7) == '\b')) {
    sVar1 = 0x3ffc;
    puVar2 = &DAT_ffff0000;
    do {
      *puVar2 = 0;
      sVar1 = sVar1 + -1;
      puVar2 = puVar2 + 1;
    } while (sVar1 != -1);
    puVar4 = (undefined1 *)(unaff_A6 + 0x11);
    sVar1 = 0x7f7;
    puVar3 = &DAT_00ffe000;
    if (unaff_A6 == 0x200000) {
      sVar1 = 0xff7;
    }
    do {
      *puVar3 = *puVar4;
      puVar4 = puVar4 + 2;
      sVar1 = sVar1 + -1;
      puVar3 = puVar3 + 1;
    } while (sVar1 != -1);
    DAT_00ff6034 = 0;
    DAT_00ff6035 = 0;
    FUN_000010e0();
    DAT_00ff601e._0_1_ = 0xff;
    DAT_00ff601e._1_1_ = 0xff;
    DAT_00ff601c = 0xf;
    DAT_00ff601a = 0;
    DAT_00ff6019 = DAT_00ff6019 | 2;
    DAT_00ff6014 = (ushort)DAT_00ffe104 << 5;
    DAT_00ff6016 = (ushort)DAT_00ffe105 << 5;
    DAT_00ff6008 = 0;
    DAT_00ff600a = 0;
    DAT_00ff600c = 0;
    DAT_00ff600e = 0;
    Ram00c00004 = 0x74000003;
    Ram00c00000 = 0;
    Ram00c00004 = 0x74020003;
    Ram00c00000 = 0;
    Ram00c00004 = 0x40000010;
    Ram00c00000 = 0;
    Ram00c00004 = 0x40020010;
    Ram00c00000 = 0;
    FUN_00000e40();
    FUN_00002e84();
    FUN_00025d46();
    FUN_00002d80();
    FUN_0001c5ac();
    FUN_0001a5f6();
    FUN_00002d00();
    FUN_00001098();
    FUN_00002ffc();
    FUN_0001a552();
    DAT_00ff6d00 = DAT_00ffe11a;
    FUN_001e41d4();
    DAT_00ff601b = 1;
    DAT_00ff6036 = 1;
    DAT_00ff619b = 0;
    DAT_00ff619d = 0;
    DAT_00ffffec = 0x27198;
    FUN_00006928();
    DAT_00ffffec = 0x2719e;
    FUN_000068ba();
    DAT_00ff6120 = 1;
    DAT_00ffffec = 0x271b2;
    FUN_00006912();
    Seed_7a6();
    return;
  }
  FUN_00000e7c();
  return;
}

