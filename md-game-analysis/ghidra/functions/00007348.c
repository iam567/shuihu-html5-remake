/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007348 */

void FUN_00007348(void)

{
  short *psVar1;
  int iVar2;
  ushort uVar3;
  
  if (DAT_00ff606a != '\0') {
    uVar3 = (ushort)DAT_00ffe10e;
    DAT_00ff606a = DAT_00ff606a - DAT_00ffe10e;
    iVar2 = (int)(short)((ushort)DAT_00ff606b << 6);
    if (*(char *)((int)&DAT_00ffe784 + iVar2 + 2) == '\0') {
      *(short *)((int)&DAT_00ffe784 + iVar2) = *(short *)((int)&DAT_00ffe784 + iVar2) - uVar3;
    }
    else if (*(char *)((int)&DAT_00ffe784 + iVar2 + 2) == '\x01') {
      *(short *)((int)&DAT_00ffe784 + iVar2) = uVar3 + *(short *)((int)&DAT_00ffe784 + iVar2);
    }
    else if (*(char *)((int)&DAT_00ffe784 + iVar2 + 2) == '\x02') {
      psVar1 = (short *)((int)&DAT_00ffe780 + iVar2 + 2);
      *psVar1 = *psVar1 - uVar3;
    }
    else if (*(char *)((int)&DAT_00ffe784 + iVar2 + 2) == '\x03') {
      psVar1 = (short *)((int)&DAT_00ffe780 + iVar2 + 2);
      *psVar1 = uVar3 + *psVar1;
    }
  }
  return;
}

