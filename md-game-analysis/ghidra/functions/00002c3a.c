/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00002c3a */

undefined8 FUN_00002c3a(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  undefined1 *unaff_A2;
  
  FUN_00003074();
  DAT_00ffe106 = *unaff_A2;
  DAT_00ffe107 = unaff_A2[1];
  DAT_00ffe108 = unaff_A2[2];
  DAT_00ffe109 = unaff_A2[3];
  DAT_00ffe104 = unaff_A2[4];
  DAT_00ffe105 = unaff_A2[5];
  DAT_00ffe002 = *(undefined2 *)(unaff_A2 + 6);
  DAT_00ffe004 = *(undefined2 *)(unaff_A2 + 8);
  DAT_00ffe006 = unaff_A2[10];
  DAT_00ffe001 = unaff_A2[0xb];
  DAT_00ffe10a = unaff_A2[0xc];
  DAT_00ffe10b = unaff_A2[0xd];
  DAT_00ffe10c = unaff_A2[0xe];
  if ((char)DAT_00ffe104 < '\0') {
    DAT_00ff6014 = (ushort)(byte)-DAT_00ffe104 * -0x20;
  }
  else {
    DAT_00ff6014 = (ushort)DAT_00ffe104 << 5;
  }
  if ((char)DAT_00ffe105 < '\0') {
    DAT_00ff6016 = (ushort)(byte)-DAT_00ffe105 * -0x20;
  }
  else {
    DAT_00ff6016 = (ushort)DAT_00ffe105 << 5;
  }
  DAT_00ff6034 = 0;
  DAT_00ff6035 = 0;
  DAT_00ff6008 = 0;
  DAT_00ff600a = 0;
  DAT_00ff600c = 0;
  DAT_00ff600e = 0;
  DAT_00ff603a = 1;
  return CONCAT44(in_D0,in_D1);
}

