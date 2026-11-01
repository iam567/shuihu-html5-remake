/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0002582a */

void FUN_0002582a(void)

{
  uint uVar1;
  uint uVar2;
  short sVar3;
  uint uVar4;
  short sVar5;
  ushort uVar6;
  bool bVar7;
  
  if (DAT_00ff619d == '\0') {
    return;
  }
  if ((DAT_00ff6004 & 1) != 0) {
    FUN_00027f08();
    FUN_000257fe();
    bVar7 = DAT_00ff619c == '\0';
    DAT_00ff619c = DAT_00ff619c + -1;
    if (bVar7) {
      DAT_00ff619c = '\x04';
    }
    FUN_000257d2();
    return;
  }
  if ((DAT_00ff6004 & 2) != 0) {
    FUN_00027f08();
    FUN_000257fe();
    DAT_00ff619c = DAT_00ff619c + 1;
    if (4 < DAT_00ff619c) {
      DAT_00ff619c = 0;
    }
    FUN_000257d2();
    return;
  }
  if ((DAT_00ff6004 & 0x40) != 0) {
    FUN_00027f18();
    uVar2 = DAT_00ffe1e4;
    uVar1 = DAT_00ffe1e0;
    if (DAT_00ff619c == '\0') {
      FUN_00025a3c();
      goto LAB_00025994;
    }
    if (DAT_00ff619c == '\x01') {
      uVar4 = 0;
      sVar3 = 0xb;
      do {
        if (((uVar1 & 1 << (uVar4 & 0x1f)) != 0) && ((uVar2 & 1 << (uVar4 & 0x1f)) != 0)) {
          sVar5 = (short)uVar4 << 6;
          uVar6 = (*(ushort *)((int)&DAT_00ffe79e + (int)sVar5) >> 3) +
                  *(short *)((int)&DAT_00ffe792 + (int)sVar5);
          if (*(ushort *)((int)&DAT_00ffe79e + (int)sVar5) < uVar6) {
            uVar6 = *(ushort *)((int)&DAT_00ffe79e + (int)sVar5);
          }
          *(ushort *)((int)&DAT_00ffe792 + (int)sVar5) = uVar6;
        }
        uVar4 = (uint)(ushort)((short)uVar4 + 1);
        sVar3 = sVar3 + -1;
      } while (sVar3 != -1);
      DAT_00ff6102 = 1;
      goto LAB_00025994;
    }
    if (DAT_00ff619c == '\x02') {
      DAT_00ff619d = 0;
      FUN_00001098();
      FUN_0000ffc2();
      return;
    }
    if (DAT_00ff619c == '\x03') {
      FUN_00024ca0();
      return;
    }
    if (DAT_00ff619c == '\x04') {
      FUN_00026ce6();
      return;
    }
  }
  if ((DAT_00ff6004 & 0x10) == 0) {
    return;
  }
  FUN_00027f18();
LAB_00025994:
  DAT_00ff619d = 0;
  DAT_00ff6036 = 0xff;
  FUN_00001098();
  return;
}

