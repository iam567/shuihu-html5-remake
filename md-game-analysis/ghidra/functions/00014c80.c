/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00014c80 */

undefined8 FUN_00014c80(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  uint extraout_D1;
  uint extraout_D1_00;
  uint extraout_D1_01;
  uint extraout_D1_02;
  uint extraout_D1_03;
  undefined1 extraout_D1b;
  uint extraout_D1_04;
  uint extraout_D1_05;
  uint uVar1;
  int unaff_A2;
  undefined2 uVar2;
  
  FUN_00014fc6();
  uVar2 = (undefined2)extraout_D1;
  if (*(char *)(unaff_A2 + 0x2a) == 'v') {
    uVar2 = (undefined2)(((extraout_D1 & 0xffff) * 0xb) / 10);
  }
  *(undefined2 *)(unaff_A2 + 0x1e) = uVar2;
  FUN_00014fc6();
  uVar1 = extraout_D1_00;
  if (*(char *)(unaff_A2 + 0x2a) == 'p') {
    uVar1 = ((extraout_D1_00 & 0xffff) * 0xb) / 10 & 0xffff;
  }
  *(char *)(unaff_A2 + 0x14) = (char)uVar1;
  FUN_00014fc6();
  uVar1 = extraout_D1_01;
  if (*(char *)(unaff_A2 + 0x2a) == 'r') {
    uVar1 = ((extraout_D1_01 & 0xffff) * 0xb) / 10 & 0xffff;
  }
  *(char *)(unaff_A2 + 0x15) = (char)uVar1;
  FUN_00014fc6();
  uVar1 = extraout_D1_02;
  if (*(char *)(unaff_A2 + 0x2a) == 'q') {
    uVar1 = ((extraout_D1_02 & 0xffff) * 0xb) / 10 & 0xffff;
  }
  *(char *)(unaff_A2 + 0x16) = (char)uVar1;
  FUN_00014fc6();
  uVar1 = extraout_D1_03;
  if (*(char *)(unaff_A2 + 0x2a) == 's') {
    uVar1 = ((extraout_D1_03 & 0xffff) * 0xb) / 10 & 0xffff;
  }
  *(char *)(unaff_A2 + 0x17) = (char)uVar1;
  FUN_00014fc6();
  *(undefined1 *)(unaff_A2 + 0x18) = extraout_D1b;
  FUN_00014fc6();
  uVar1 = extraout_D1_04;
  if (*(char *)(unaff_A2 + 0x2a) == 't') {
    uVar1 = ((extraout_D1_04 & 0xffff) * 0xb) / 10 & 0xffff;
  }
  *(char *)(unaff_A2 + 0x19) = (char)uVar1;
  FUN_00014fc6();
  uVar1 = extraout_D1_05;
  if (*(char *)(unaff_A2 + 0x2a) == 'u') {
    uVar1 = ((extraout_D1_05 & 0xffff) * 0xb) / 10 & 0xffff;
  }
  *(char *)(unaff_A2 + 0x1a) = (char)uVar1;
  *(undefined *)(unaff_A2 + 0x1b) =
       (&DAT_00014d8c)[(short)(ushort)(byte)(*(char *)(unaff_A2 + 0x24) - 1)];
  return CONCAT44(in_D0,in_D1);
}

