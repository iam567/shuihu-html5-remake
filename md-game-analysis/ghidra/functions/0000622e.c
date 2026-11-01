/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000622e */

void FUN_0000622e(void)

{
  ushort uVar1;
  
  if (DAT_00ff604c != '\0') {
    uVar1 = (ushort)DAT_00ffe10e;
    DAT_00ff604c = DAT_00ff604c - DAT_00ffe10e;
    if (DAT_00ff604d == '\0') {
      DAT_00ffe1f2 = DAT_00ffe1f2 - uVar1;
    }
    else if (DAT_00ff604d == '\x01') {
      DAT_00ffe1f2 = uVar1 + DAT_00ffe1f2;
    }
    else if (DAT_00ff604d == '\x02') {
      DAT_00ffe1f0 = DAT_00ffe1f0 - uVar1;
    }
    else {
      DAT_00ffe1f0 = uVar1 + DAT_00ffe1f0;
    }
  }
  return;
}

