/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000036e */

void FUN_0000036e(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  
  uVar4 = DAT_00ffefa2;
  uVar3 = DAT_00ffef82;
  uVar2 = DAT_00ffef22;
  uVar1 = DAT_00ffef02;
  if (((DAT_00ff6018 & 1) != 0) && ((DAT_00ff610d & (byte)DAT_00ff6010) == 0)) {
    if ((DAT_00ff6018 & 4) == 0) {
      DAT_00ffef82 = DAT_00ffef84;
      DAT_00ffef84 = DAT_00ffef86;
      DAT_00ffef86 = uVar3;
      DAT_00ffef02 = DAT_00ffef04;
      DAT_00ffef04 = DAT_00ffef06;
      DAT_00ffef06 = uVar1;
      DAT_00ff6001 = 0xff;
    }
    else {
      DAT_00ffef82 = DAT_00ffef84;
      DAT_00ffef84 = uVar3;
      DAT_00ffef02 = DAT_00ffef04;
      DAT_00ffef04 = uVar1;
      DAT_00ff6001 = 0xff;
    }
  }
  if (((DAT_00ff6018 & 2) != 0) && ((DAT_00ff610e & (byte)DAT_00ff6010) == 0)) {
    if ((DAT_00ff6018 & 8) == 0) {
      DAT_00ffefa2 = DAT_00ffefa4;
      DAT_00ffefa4 = DAT_00ffefa6;
      DAT_00ffefa6 = uVar4;
      DAT_00ffef22 = DAT_00ffef24;
      DAT_00ffef24 = DAT_00ffef26;
      DAT_00ffef26 = uVar2;
      DAT_00ff6001 = 0xff;
    }
    else {
      DAT_00ffefa2 = DAT_00ffefa4;
      DAT_00ffefa4 = uVar4;
      DAT_00ffef22 = DAT_00ffef24;
      DAT_00ffef24 = uVar2;
      DAT_00ff6001 = 0xff;
    }
  }
  return;
}

