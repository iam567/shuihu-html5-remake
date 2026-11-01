/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00006d28 */

void FUN_00006d28(void)

{
  ushort uVar1;
  short sVar2;
  byte *pbVar3;
  
  uVar1 = (ushort)DAT_00ffe106;
  pbVar3 = (byte *)((int)&DAT_00ffb000 +
                   (int)(short)(ushort)DAT_00ffe104 + (uint)DAT_00ffe105 * (uint)uVar1);
  sVar2 = 6;
  do {
    if (*pbVar3 < 0x7f) {
      FUN_0000309a();
    }
    else {
      FUN_0000353c();
    }
    pbVar3 = pbVar3 + (short)uVar1;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}

