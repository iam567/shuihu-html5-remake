/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000db8c */

void FUN_0000db8c(void)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  
  uVar2 = (uint)DAT_00ffe1fa;
  pcVar4 = (char *)((int)&DAT_00ffe780 + (int)(short)(DAT_00ffe1fa << 6));
  sVar1 = 0xb - DAT_00ffe1fa;
  uVar3 = DAT_00ffe1e0;
  do {
    if (*pcVar4 == '\0') {
      uVar3 = uVar3 & ~(1 << (uVar2 & 0x1f));
      DAT_00ffe1e0 = uVar3;
    }
    else if ((uVar3 & 1 << (uVar2 & 0x1f)) != 0) {
      DAT_00ff606b = (char)uVar2;
      FUN_00007c14();
      DAT_00ff6085 = 1;
      return;
    }
    uVar2 = (uint)(byte)((char)uVar2 + 1);
    pcVar4 = pcVar4 + 0x40;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00ff6102 = 1;
  return;
}

