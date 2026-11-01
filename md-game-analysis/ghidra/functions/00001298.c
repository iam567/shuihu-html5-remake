/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00001298 */

void FUN_00001298(void)

{
  short sVar1;
  undefined4 in_D1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  undefined6 uVar6;
  
  sVar1 = 7;
  pcVar5 = &DAT_00ffe000;
  uVar4 = 0;
  uVar2 = CONCAT22((short)((uint)in_D1 >> 0x10),DAT_00ff6010);
  if ((DAT_00ff6010 & 1) != 0) {
    pcVar5 = &DAT_00ffe010;
    uVar4 = 1;
  }
  do {
    uVar6 = CONCAT24(sVar1,uVar2);
    if ((*pcVar5 != '\0') &&
       (uVar3 = CONCAT22((short)((uint)uVar2 >> 0x10),DAT_00ff601e), uVar6 = CONCAT24(sVar1,uVar3),
       (uVar3 & 1 << (uVar4 & 0x1f)) != 0)) {
      DAT_00ff601e = DAT_00ff601e & ~(ushort)(1 << (uVar4 & 0x1f));
      uVar6 = FUN_000012ee();
    }
    uVar2 = (undefined4)uVar6;
    uVar4 = (uint)(byte)((char)uVar4 + 2);
    pcVar5 = pcVar5 + 0x20;
    sVar1 = (short)((uint6)uVar6 >> 0x20) + -1;
  } while (sVar1 != -1);
  return;
}

