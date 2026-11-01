/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000baec */

void FUN_0000baec(void)

{
  int iVar1;
  bool bVar2;
  
  if (DAT_00ff60b8 == '\0') {
LAB_0000bdda:
    if ((DAT_00ff6004 & 0x10) != 0) {
      FUN_00027f18();
      FUN_00001098();
      DAT_00ff6085 = 1;
    }
  }
  else {
    if ((DAT_00ff6004 & 1) == 0) {
      if ((DAT_00ff6004 & 2) == 0) {
        if ((DAT_00ff6004 & 0x40) != 0) {
          FUN_00027f18();
          iVar1 = (int)(short)(ushort)DAT_00ff60b7 + (int)(short)((ushort)DAT_00ff606b << 6);
          if (*(char *)((int)&DAT_00ffe780 + iVar1 + 0x2b) == '\0') {
            return;
          }
          DAT_00ff60bc = *(char *)((int)&DAT_00ffe780 + iVar1 + 0x26);
          DAT_00ff60bb = *(byte *)((int)&PTR_DAT_00028e5b +
                                  (int)(short)((ushort)(byte)(DAT_00ff60bc - 1) << 3));
          if (DAT_00ff60bb == 3) {
            FUN_0000d0c6();
            return;
          }
          if (DAT_00ff60bb == 4) {
            FUN_0000d0c6();
            return;
          }
          if (DAT_00ff60bb == 5) {
            FUN_0000d0c6();
            return;
          }
          if (DAT_00ff60bb == 6) {
            FUN_0000d0c6();
            return;
          }
          if (DAT_00ff60bb == 7) {
            FUN_0001524c();
            return;
          }
          if (DAT_00ff60bb == 8) {
            FUN_0001524c();
            return;
          }
          if (DAT_00ff60bb == 9) {
            FUN_0001524c();
            return;
          }
          if (DAT_00ff60bb == 10) {
            FUN_0001524c();
            return;
          }
          if (DAT_00ff60bb == 0xb) {
            FUN_000150ee();
            return;
          }
          if (DAT_00ff60bb == 0xd) {
            FUN_0001524c();
            return;
          }
          if (DAT_00ff60bb == 0xe) {
            FUN_00006912();
            FUN_00001098();
            FUN_0000a596();
            FUN_00006c86();
            FUN_0000a4cc();
            if (DAT_00ff7180 == 0xff) {
              DAT_00ff6085 = 4;
              return;
            }
            DAT_00ff6085 = 0x10;
            return;
          }
          if (DAT_00ff60bb < 2) {
            FUN_00006912();
            FUN_00001098();
            FUN_00009b32();
            FUN_00006c86();
            FUN_00009b9a();
            if (DAT_00ff7180 == 0xff) {
              DAT_00ff6085 = 8;
              return;
            }
            DAT_00ff6036 = 0;
            DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff7180 << 6) + 2)
                           >> 5;
            DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff7180 << 6))
                           >> 5;
            DAT_00ff605a = 1;
            DAT_00ff6085 = 4;
            DAT_00ff6087 = 0;
            return;
          }
          FUN_00006912();
          FUN_00001098();
          FUN_0000a596();
          FUN_00006c86();
          FUN_0000a4cc();
          if (DAT_00ff7180 == 0xff) {
            DAT_00ff6085 = 4;
            return;
          }
          DAT_00ff6036 = 0;
          DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + (short)((ushort)DAT_00ff7180 << 6) + 2) >>
                         5;
          DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + (int)(short)((ushort)DAT_00ff7180 << 6))
                         >> 5;
          DAT_00ff605a = 1;
          DAT_00ff6085 = 4;
          DAT_00ff6087 = 0;
          return;
        }
        goto LAB_0000bdda;
      }
      FUN_00027f08();
      FUN_0000beb0();
      DAT_00ff60b7 = DAT_00ff60b7 + 1;
      if ((char)(DAT_00ff60b8 + -1) < (char)DAT_00ff60b7) {
        DAT_00ff60b7 = 0;
      }
    }
    else {
      FUN_00027f08();
      FUN_0000beb0();
      bVar2 = DAT_00ff60b7 == 0;
      DAT_00ff60b7 = DAT_00ff60b7 - 1;
      if (bVar2) {
        DAT_00ff60b7 = DAT_00ff60b8 - 1;
      }
    }
    FUN_0000bdfc();
    FUN_0001435e();
  }
  return;
}

