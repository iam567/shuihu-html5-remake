/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00027a3e */

void FUN_00027a3e(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  
  uVar4 = DAT_00ffefe6;
  uVar3 = DAT_00ffefa8;
  uVar2 = DAT_00ffef66;
  uVar1 = DAT_00ffef28;
  if (((DAT_00ff611a & 1) != 0) && ((DAT_00ff610d & (byte)DAT_00ff6010) == 0)) {
    DAT_00ffefe6 = DAT_00ffefe4;
    DAT_00ffefe4 = DAT_00ffefe2;
    DAT_00ffefe2 = uVar4;
    DAT_00ffef66 = DAT_00ffef64;
    DAT_00ffef64 = DAT_00ffef62;
    DAT_00ffef62 = uVar2;
    DAT_00ff6001 = 0xff;
  }
  if (((DAT_00ff611a & 2) != 0) && ((DAT_00ff610e & (byte)DAT_00ff6010) == 0)) {
    DAT_00ffefa8 = DAT_00ffefa6;
    DAT_00ffefa6 = DAT_00ffefa4;
    DAT_00ffefa4 = DAT_00ffefa2;
    DAT_00ffefa2 = uVar3;
    DAT_00ffef28 = DAT_00ffef26;
    DAT_00ffef26 = DAT_00ffef24;
    DAT_00ffef24 = DAT_00ffef22;
    DAT_00ffef22 = uVar1;
    DAT_00ff6001 = 0xff;
  }
  return;
}

