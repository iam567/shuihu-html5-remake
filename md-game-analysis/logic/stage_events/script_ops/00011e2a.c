/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00011e2a */

void FUN_00011e2a(void)

{
  ushort uVar1;
  short sVar2;
  char *pcVar3;
  char *pcVar4;
  ushort *unaff_A3;
  ushort *puVar5;
  
  FUN_000142a8();
  DAT_00ffe1fa = *unaff_A3;
  uVar1 = DAT_00ffe1fa;
  for (pcVar3 = (char *)((int)&DAT_00ffe780 + (int)(short)(DAT_00ffe1fa << 6)); *pcVar3 != '\0';
      pcVar3 = pcVar3 + 0x40) {
    uVar1 = uVar1 + 1;
  }
  DAT_00ff613e = (undefined1)uVar1;
  DAT_00ffe1ec = DAT_00ffe1ec | 1 << (uVar1 & 0x1f);
  sVar2 = 0xf;
  pcVar4 = pcVar3;
  puVar5 = unaff_A3 + 1;
  do {
    DAT_00ff6130 = puVar5 + 2;
    *(undefined4 *)pcVar4 = *(undefined4 *)puVar5;
    sVar2 = sVar2 + -1;
    pcVar4 = pcVar4 + 4;
    puVar5 = DAT_00ff6130;
  } while (sVar2 != -1);
  *pcVar3 = '\0';
  DAT_00ff613a = *(ushort *)(pcVar3 + 2) >> 5;
  DAT_00ff613c = *(ushort *)(pcVar3 + 4) >> 5;
  func_0x00014184();
  sVar2 = DAT_00ff613c << 5;
  *(ushort *)(pcVar3 + 2) = DAT_00ff613a << 5;
  *(short *)(pcVar3 + 4) = sVar2;
  return;
}

