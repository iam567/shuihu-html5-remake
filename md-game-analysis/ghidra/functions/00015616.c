/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00015616 */

void FUN_00015616(void)

{
  int iVar1;
  undefined1 extraout_var;
  undefined1 extraout_var_00;
  bool bVar2;
  
  if (DAT_00ff60b8 == '\0') {
LAB_000157fa:
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
          DAT_00ff60bc = *(char *)((int)&DAT_00ffe788 +
                                  (int)(short)(ushort)DAT_00ff60b7 +
                                  (int)(short)((ushort)DAT_00ff606b << 6));
          DAT_00ff60bb = *(byte *)((int)&PTR_DAT_00028e5b +
                                  (int)(short)((ushort)(byte)(DAT_00ff60bc - 1) << 3));
          if (5 < DAT_00ff60bb) {
            FUN_00006912();
            FUN_00001098();
            FUN_0001581c();
            FUN_00006c86();
            FUN_000159fc();
            if (DAT_00ff7180 == -1) {
              DAT_00ff6085 = 8;
              return;
            }
            iVar1 = (int)(short)(CONCAT11(extraout_var_00,DAT_00ff7180) << 6);
            DAT_00ff6036 = 0;
            DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + iVar1 + 2) >> 5;
            DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + iVar1) >> 5;
            DAT_00ff605a = 1;
            DAT_00ff6085 = 0x13;
            DAT_00ff6087 = 0;
            return;
          }
          FUN_00006912();
          FUN_00001098();
          FUN_0001581c();
          FUN_00006c86();
          FUN_000158be();
          if (DAT_00ff7180 == -1) {
            DAT_00ff6085 = 8;
            return;
          }
          iVar1 = (int)(short)(CONCAT11(extraout_var,DAT_00ff7180) << 6);
          DAT_00ff6036 = 0;
          DAT_00ff6052 = *(ushort *)((int)&DAT_00ffe780 + iVar1 + 2) >> 5;
          DAT_00ff6054 = *(ushort *)((int)&DAT_00ffe784 + iVar1) >> 5;
          DAT_00ff605a = 1;
          DAT_00ff6085 = 0x13;
          DAT_00ff6087 = 0;
          return;
        }
        goto LAB_000157fa;
      }
      FUN_00027f08();
      FUN_00015aba();
      DAT_00ff60b7 = DAT_00ff60b7 + 1;
      if ((char)(DAT_00ff60b8 + -1) < (char)DAT_00ff60b7) {
        DAT_00ff60b7 = 0;
      }
    }
    else {
      FUN_00027f08();
      FUN_00015aba();
      bVar2 = DAT_00ff60b7 == 0;
      DAT_00ff60b7 = DAT_00ff60b7 - 1;
      if (bVar2) {
        DAT_00ff60b7 = DAT_00ff60b8 - 1;
      }
    }
    FUN_0000b93c();
  }
  return;
}

