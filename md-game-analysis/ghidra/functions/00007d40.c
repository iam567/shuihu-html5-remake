/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007d40 */

void FUN_00007d40(void)

{
  short sVar1;
  undefined4 *puVar2;
  
  if (((DAT_00ff6102 != '\0') && ((DAT_00ff603d & 1) == 0)) && (DAT_00ff605a == '\0')) {
    DAT_00ff6102 = '\0';
    FUN_00006912();
    FUN_00006928();
    DAT_00ffe1f7 = DAT_00ffe1f7 + 1;
    if (DAT_00ffe1f7 < 3) {
      if (DAT_00ffe1f7 != 2) {
        if (DAT_00ffe1fa < 0xc) {
          DAT_00ff6036 = 0;
          DAT_00ffe1e0 = DAT_00ffe1ec;
          DAT_00ff606b = (undefined1)DAT_00ffe1fa;
          DAT_00ff6080 = DAT_00ffe1e4;
          puVar2 = &DAT_00ffe780;
          sVar1 = 0xb;
          do {
            *(undefined1 *)((int)puVar2 + 1) = 0x10;
            *(undefined1 *)((int)puVar2 + 6) = 1;
            puVar2 = puVar2 + 0x10;
            sVar1 = sVar1 + -1;
          } while (sVar1 != -1);
          FUN_0000ee70();
          DAT_00ff611c = 1;
          return;
        }
        DAT_00ffe1f7 = 2;
      }
      DAT_00ff6036 = 0;
      DAT_00ffe1e0 = DAT_00ffe1e8;
      puVar2 = &DAT_00ffe780;
      sVar1 = DAT_00ffe1fa + -1;
      do {
        *(undefined1 *)((int)puVar2 + 1) = 0x10;
        *(undefined1 *)((int)puVar2 + 6) = 1;
        puVar2 = puVar2 + 0x10;
        sVar1 = sVar1 + -1;
      } while (sVar1 != -1);
      DAT_00ff6080 = DAT_00ffe1e4;
      FUN_00007b8e();
      FUN_0000ee70();
      DAT_00ff606b = 0xc;
      DAT_00ff6105 = 1;
    }
    else {
      DAT_00ffe1f7 = 0;
      DAT_00ffe1e0 = DAT_00ffe1e4;
      DAT_00ff606b = 0;
      DAT_00ffe1f5 = DAT_00ffe1f5 + '\x01';
      FUN_0000f012();
      DAT_00ff6104 = 1;
    }
  }
  return;
}

