/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00012074 */

void FUN_00012074(void)

{
  ushort uVar1;
  uint uVar2;
  char *pcVar3;
  
  if ((((DAT_00ff603d & 1) == 0) &&
      ((**(code **)(&UNK_000120e8 + (short)((ushort)DAT_00ffe10f << 2)))(), DAT_00ffe1f7 == '\0'))
     && (DAT_00ff6085 == '\0')) {
    pcVar3 = (char *)&DAT_00ffe780;
    uVar1 = (ushort)(byte)(DAT_00ffe1f4 - 1);
    uVar2 = 0;
    do {
      if ((*pcVar3 != '\0') && ((DAT_00ffe1e0 & 1 << (uVar2 & 0x1f)) != 0)) {
        return;
      }
      uVar2 = (uint)(ushort)((short)uVar2 + 1);
      pcVar3 = pcVar3 + 0x40;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0xffff);
    DAT_00ff6102 = 1;
  }
  return;
}

