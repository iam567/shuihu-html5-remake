/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000097a */

void FUN_0000097a(void)

{
  byte unaff_D2b;
  
  if (DAT_00ff6036 == '\0') {
    return;
  }
  if ((DAT_00ff603d & 1) != 0) {
    return;
  }
  if (DAT_00ff6039 != '\0') {
    return;
  }
  if (DAT_00ff6030 != '\0') {
    return;
  }
  FUN_000031ea();
  if ((DAT_00ff6004 & 0x40) != 0) {
    FUN_0000329e();
    if ((0x7f < unaff_D2b) && (unaff_D2b < 0xb0)) {
      DAT_00ff603c = unaff_D2b;
      FUN_00000df4();
      return;
    }
    DAT_00ff603c = unaff_D2b;
    FUN_000182aa();
    return;
  }
  if ((DAT_00ff6004 & 0x10) != 0) {
    return;
  }
  if ((DAT_00ff6004 & 0x20) != 0) {
    return;
  }
  if ((DAT_00ff6004 & 0x80) != 0) {
    FUN_00027f18();
    FUN_000254ce();
    return;
  }
  if ((DAT_00ff6003 & 4) == 0) {
    if ((DAT_00ff6003 & 8) == 0) {
      if ((DAT_00ff6003 & 1) == 0) {
        if ((DAT_00ff6003 & 2) == 0) {
          return;
        }
        DAT_00ffe001 = 4;
        DAT_00ff601e._1_1_ = (byte)DAT_00ff601e | 1;
        DAT_00ffe006 = 1;
        FUN_0000329e();
        if (0x4f < unaff_D2b) goto LAB_00000d1e;
        DAT_00ff603c = unaff_D2b;
        FUN_00007af6();
        if ((DAT_00ff6037 & 1) != 0) {
          return;
        }
        if (((short)DAT_00ff6022 < 0xe0) || ((char)(DAT_00ffe107 + -7) == DAT_00ffe105)) {
          if (0x13f < (short)DAT_00ff6022) {
            return;
          }
          DAT_00ffe006 = '\x01';
        }
        else {
          DAT_00ffe105 = DAT_00ffe105 + '\x01';
          DAT_00ff618f = DAT_00ff618f | 2;
          FUN_000032f2();
          DAT_00ff6038 = 1;
          DAT_00ff6039 = ' ';
          DAT_00ffe006 = '\x01';
        }
      }
      else {
        DAT_00ffe001 = 0;
        DAT_00ff601e._1_1_ = (byte)DAT_00ff601e | 1;
        DAT_00ffe006 = 0;
        FUN_0000329e();
        if (0x4f < unaff_D2b) {
LAB_00000d1e:
          DAT_00ff603c = unaff_D2b;
          FUN_00000d92();
          return;
        }
        DAT_00ff603c = unaff_D2b;
        FUN_00007af6();
        if ((DAT_00ff6037 & 1) != 0) {
          return;
        }
        if ((DAT_00ff6022 < 0xe1) && (DAT_00ffe105 != '\0')) {
          DAT_00ffe105 = DAT_00ffe105 + -1;
          DAT_00ff618f = DAT_00ff618f | 1;
          FUN_000032c4();
          DAT_00ff6038 = 0;
          DAT_00ff6039 = ' ';
          DAT_00ffe006 = '\0';
        }
        else {
          DAT_00ffe006 = '\0';
        }
      }
    }
    else {
      DAT_00ffe001 = 0xc;
      DAT_00ff601e._1_1_ = (byte)DAT_00ff601e | 1;
      DAT_00ffe006 = 3;
      FUN_0000329e();
      if (0x4f < unaff_D2b) goto LAB_00000d1e;
      DAT_00ff603c = unaff_D2b;
      FUN_00007af6();
      if ((DAT_00ff6037 & 1) != 0) {
        return;
      }
      if (0x19f < (short)DAT_00ff6020) {
        return;
      }
      if (((short)DAT_00ff6020 < 0x120) || ((char)(DAT_00ffe106 + -10) == DAT_00ffe104)) {
        DAT_00ffe006 = '\x03';
      }
      else {
        DAT_00ffe104 = DAT_00ffe104 + '\x01';
        DAT_00ff618f = DAT_00ff618f | 8;
        FUN_00003354();
        DAT_00ff6038 = 3;
        DAT_00ff6039 = ' ';
        DAT_00ffe006 = '\x03';
      }
    }
  }
  else {
    DAT_00ffe001 = 8;
    DAT_00ff601e._1_1_ = (byte)DAT_00ff601e | 1;
    DAT_00ffe006 = 2;
    FUN_0000329e();
    if (0x4f < unaff_D2b) goto LAB_00000d1e;
    DAT_00ff603c = unaff_D2b;
    FUN_00007af6();
    if ((DAT_00ff6037 & 1) != 0) {
      return;
    }
    if (DAT_00ff6020 < 0x81) {
      return;
    }
    if ((DAT_00ff6020 < 0x101) && (DAT_00ffe104 != '\0')) {
      DAT_00ffe104 = DAT_00ffe104 + -1;
      DAT_00ff618f = DAT_00ff618f | 4;
      FUN_00003326();
      DAT_00ff6038 = 2;
      DAT_00ff6039 = ' ';
      DAT_00ffe006 = '\x02';
    }
    else {
      DAT_00ffe006 = '\x02';
    }
  }
  DAT_00ff6030 = 0x20;
  DAT_00ffe001 = DAT_00ffe006 << 2;
  DAT_00ff601e._1_1_ = (byte)DAT_00ff601e | 1;
  FUN_00000d30();
  return;
}

