/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001a3ee */

void FUN_0001a3ee(void)

{
  char cVar1;
  ushort uVar2;
  
  uVar2 = (ushort)(byte)(&DAT_00ff9000)[(short)(ushort)DAT_00ff617a];
  cVar1 = (&DAT_00ffe480)[(short)uVar2];
  if (cVar1 != '\0') {
    *DAT_00ff60e8 = (&DAT_00ffe400)[(short)uVar2];
    (&DAT_00ffe480)[(short)uVar2] = cVar1 + -1;
    FUN_00019cf6();
  }
  return;
}

