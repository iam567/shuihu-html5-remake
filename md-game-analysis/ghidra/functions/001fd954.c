/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001fd954 */

undefined4 FUN_001fd954(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined4 in_D0;
  
  uVar3 = DAT_00ffcf3e;
  uVar2 = DAT_00ffcf3c;
  uVar1 = DAT_00ffcf3a;
  DAT_00ff0f82 = DAT_00ff0f82 + '\x01';
  if ('\t' < DAT_00ff0f82) {
    DAT_00ff0f82 = '\0';
    DAT_00ffcf3a = DAT_00ffcf3c;
    DAT_00ffcf3c = DAT_00ffcf3e;
    DAT_00ffcf3e = uVar1;
    Ram00c00004 = 0xc03a0000;
    Ram00c00000 = uVar2;
    Ram00c00000 = uVar3;
    Ram00c00000 = uVar1;
  }
  return in_D0;
}

