/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001b538 */

void FUN_0001b538(void)

{
  ushort uVar1;
  ushort in_D1w;
  char *pcVar2;
  char *pcVar3;
  
  pcVar2 = *(char **)(&DAT_0001b562 + (short)((in_D1w & 0xff) << 2));
  DAT_00ff618a = *pcVar2;
  uVar1 = (ushort)(byte)(*pcVar2 - 1);
  pcVar3 = &DAT_00ff9000;
  do {
    pcVar2 = pcVar2 + 1;
    *pcVar3 = *pcVar2;
    uVar1 = uVar1 - 1;
    pcVar3 = pcVar3 + 1;
  } while (uVar1 != 0xffff);
  return;
}

