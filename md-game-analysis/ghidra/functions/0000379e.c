/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000379e */

void FUN_0000379e(void)

{
  ushort uVar1;
  byte bVar2;
  char extraout_D1b;
  char extraout_D1b_00;
  char extraout_D1b_01;
  char extraout_D1b_02;
  char extraout_D1b_03;
  char extraout_D1b_04;
  char extraout_D1b_05;
  char extraout_D1b_06;
  
  if (DAT_00ff6039 != '\0') {
    bVar2 = DAT_00ffe10e;
    if (DAT_00ffe10e == 0) {
      if ((DAT_00ff6010 & 1) == 0) {
        return;
      }
      bVar2 = 1;
    }
    uVar1 = (ushort)bVar2;
    if (DAT_00ff6038 == '\0') {
      DAT_00ff6016 = DAT_00ff6016 - uVar1;
      DAT_00ff600a = DAT_00ff600a - uVar1;
      FUN_00003a46();
      DAT_00ff603a = 1;
      DAT_00ff6039 = DAT_00ff6039 - extraout_D1b;
    }
    else if (DAT_00ff6038 == '\x01') {
      DAT_00ff6016 = uVar1 + DAT_00ff6016;
      DAT_00ff600a = uVar1 + DAT_00ff600a;
      FUN_00003a0a();
      DAT_00ff603a = 1;
      DAT_00ff6039 = DAT_00ff6039 - extraout_D1b_00;
    }
    else if (DAT_00ff6038 == '\x02') {
      DAT_00ff6014 = DAT_00ff6014 - uVar1;
      DAT_00ff6008 = uVar1 + DAT_00ff6008;
      FUN_00003992();
      DAT_00ff603a = 1;
      DAT_00ff6039 = DAT_00ff6039 - extraout_D1b_01;
    }
    else if (DAT_00ff6038 == '\x03') {
      DAT_00ff6014 = uVar1 + DAT_00ff6014;
      DAT_00ff6008 = DAT_00ff6008 - uVar1;
      FUN_000039ce();
      DAT_00ff603a = 1;
      DAT_00ff6039 = DAT_00ff6039 - extraout_D1b_02;
    }
    else if (DAT_00ff6038 == '\x04') {
      DAT_00ff6014 = DAT_00ff6014 - uVar1;
      DAT_00ff6016 = DAT_00ff6016 - uVar1;
      DAT_00ff6008 = uVar1 + DAT_00ff6008;
      DAT_00ff600a = DAT_00ff600a - uVar1;
      FUN_00003992();
      FUN_00003a46();
      DAT_00ff603a = 1;
      DAT_00ff6039 = DAT_00ff6039 - extraout_D1b_03;
    }
    else if (DAT_00ff6038 == '\x05') {
      DAT_00ff6014 = uVar1 + DAT_00ff6014;
      DAT_00ff6016 = DAT_00ff6016 - uVar1;
      DAT_00ff6008 = DAT_00ff6008 - uVar1;
      DAT_00ff600a = DAT_00ff600a - uVar1;
      FUN_000039ce();
      FUN_00003a46();
      DAT_00ff603a = 1;
      DAT_00ff6039 = DAT_00ff6039 - extraout_D1b_04;
    }
    else if (DAT_00ff6038 == '\x06') {
      DAT_00ff6014 = DAT_00ff6014 - uVar1;
      DAT_00ff6016 = uVar1 + DAT_00ff6016;
      DAT_00ff6008 = uVar1 + DAT_00ff6008;
      DAT_00ff600a = uVar1 + DAT_00ff600a;
      FUN_00003992();
      FUN_00003a0a();
      DAT_00ff603a = 1;
      DAT_00ff6039 = DAT_00ff6039 - extraout_D1b_05;
    }
    else if (DAT_00ff6038 == '\a') {
      DAT_00ff6014 = uVar1 + DAT_00ff6014;
      DAT_00ff6016 = uVar1 + DAT_00ff6016;
      DAT_00ff6008 = DAT_00ff6008 - uVar1;
      DAT_00ff600a = uVar1 + DAT_00ff600a;
      FUN_000039ce();
      FUN_00003a0a();
      DAT_00ff603a = 1;
      DAT_00ff6039 = DAT_00ff6039 - extraout_D1b_06;
    }
  }
  return;
}

