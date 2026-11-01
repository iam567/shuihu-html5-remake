/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001611a */

void FUN_0001611a(void)

{
  if (DAT_00ff6155 != 0) {
    DAT_00ff6155 = DAT_00ff6155 + 1;
    if (DAT_00ff6155 < 0x32) {
      Ram00c00004 = 0x74000003;
      Ram00c00000 = DAT_00ff6008;
      Ram00c00004 = 0x40000010;
      Ram00c00000 = DAT_00ff600a -
                    *(short *)((int)&PTR_DAT_00014744 + (int)(short)((DAT_00ff6155 - 2) * 2));
    }
    else {
      DAT_00ff6155 = 0;
      DAT_00ff603d = DAT_00ff603d | 2;
      FUN_00001098();
      Ram00c00004 = 0x74000003;
      Ram00c00000 = DAT_00ff6008;
      Ram00c00004 = 0x40000010;
      Ram00c00000 = DAT_00ff600a;
    }
  }
  return;
}

