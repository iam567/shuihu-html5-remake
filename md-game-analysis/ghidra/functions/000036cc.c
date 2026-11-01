/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000036cc */

undefined4 FUN_000036cc(void)

{
  undefined4 in_D0;
  short sVar1;
  ushort uVar2;
  int iVar3;
  
  if (DAT_00ff6030 != '\0') {
    uVar2 = (ushort)DAT_00ffe10d;
    DAT_00ff6030 = DAT_00ff6030 - DAT_00ffe10d;
    iVar3 = 0xffe000;
    sVar1 = 7;
    do {
      if (*(char *)(iVar3 + 6) == '\0') {
        *(short *)(iVar3 + 4) = *(short *)(iVar3 + 4) - uVar2;
      }
      else if (*(char *)(iVar3 + 6) == '\x01') {
        *(short *)(iVar3 + 4) = uVar2 + *(short *)(iVar3 + 4);
      }
      else if (*(char *)(iVar3 + 6) == '\x02') {
        *(short *)(iVar3 + 2) = *(short *)(iVar3 + 2) - uVar2;
      }
      else if (*(char *)(iVar3 + 6) == '\x03') {
        *(short *)(iVar3 + 2) = uVar2 + *(short *)(iVar3 + 2);
      }
      else if (*(char *)(iVar3 + 6) == '\x05') {
        *(short *)(iVar3 + 2) = uVar2 + *(short *)(iVar3 + 2);
        *(short *)(iVar3 + 4) = *(short *)(iVar3 + 4) - uVar2;
      }
      else if (*(char *)(iVar3 + 6) == '\a') {
        *(short *)(iVar3 + 2) = uVar2 + *(short *)(iVar3 + 2);
        *(short *)(iVar3 + 4) = uVar2 + *(short *)(iVar3 + 4);
      }
      else if (*(char *)(iVar3 + 6) == '\x06') {
        *(short *)(iVar3 + 2) = *(short *)(iVar3 + 2) - uVar2;
        *(short *)(iVar3 + 4) = uVar2 + *(short *)(iVar3 + 4);
      }
      else if (*(char *)(iVar3 + 6) == '\x04') {
        *(short *)(iVar3 + 2) = *(short *)(iVar3 + 2) - uVar2;
        *(short *)(iVar3 + 4) = *(short *)(iVar3 + 4) - uVar2;
      }
      iVar3 = iVar3 + 0x10;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
  }
  return in_D0;
}

