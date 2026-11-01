/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00004b8a */

void FUN_00004b8a(void)

{
  int iVar1;
  undefined2 uVar2;
  ushort uVar3;
  bool bVar4;
  
  if ((DAT_00ff6004 & 0x40) == 0) {
    if ((DAT_00ff6004 & 0x10) == 0) {
      if ((DAT_00ff6004 & 8) == 0) {
        if ((DAT_00ff6004 & 4) != 0) {
          FUN_00027f08();
          do {
            bVar4 = DAT_00ff605f == 0;
            DAT_00ff605f = DAT_00ff605f - 1;
            if (bVar4) {
              DAT_00ff605f = 3;
            }
          } while ((DAT_00ff606c & '\x01' << (DAT_00ff605f & 7)) == 0);
        }
      }
      else {
        FUN_00027f08();
        do {
          DAT_00ff605f = DAT_00ff605f + 1;
          if (3 < DAT_00ff605f) {
            DAT_00ff605f = 0;
          }
        } while ((DAT_00ff606c & '\x01' << (DAT_00ff605f & 7)) == 0);
      }
      FUN_00009e2e();
      FUN_00009efc();
    }
    else {
      FUN_00027f18();
      FUN_00006912();
      FUN_00006928();
      FUN_00001098();
      uVar2 = DAT_00ff608c;
      iVar1 = (int)(short)((ushort)DAT_00ff606b << 6);
      DAT_00ffe1f0 = *(undefined2 *)((int)&DAT_00ffe780 + iVar1 + 2);
      DAT_00ffe1f2 = *(undefined2 *)((int)&DAT_00ffe784 + iVar1);
      *(undefined2 *)((int)&DAT_00ffe780 + iVar1 + 2) = DAT_00ff608a;
      *(undefined2 *)((int)&DAT_00ffe784 + iVar1) = uVar2;
      FUN_00007c14();
      DAT_00ff6085 = 0;
    }
  }
  else {
    FUN_00027f18();
    if (DAT_00ff605f == 0) {
      FUN_0000b606();
      FUN_000142e8();
      DAT_00ff6085 = 0xb;
    }
    else if (DAT_00ff605f == 1) {
      FUN_00006912();
      FUN_00006928();
      FUN_00001098();
      FUN_00006f0e();
      FUN_00006986();
      FUN_00006c86();
      DAT_00ff6085 = 2;
    }
    else if (DAT_00ff605f == 2) {
      DAT_00ffe1e0 = DAT_00ffe1e0 & ~(1 << (DAT_00ff606b & 0x1f));
      DAT_00ff6080 = DAT_00ff6080 | 1 << (DAT_00ff606b & 0x1f);
      uVar3 = (ushort)DAT_00ff606b;
      *(undefined1 *)((int)&DAT_00ffe780 + (short)(uVar3 << 6) + 1) = 0x10;
      *(undefined1 *)((int)&DAT_00ffe784 + (short)(uVar3 << 6) + 2) = 1;
      if ((DAT_00ff606c & 2) == 0) {
        FUN_00001098();
        DAT_00ff6085 = 0;
      }
      else {
        iVar1 = (int)(short)((ushort)DAT_00ff606b << 6);
        (&DAT_00ffe79d)[iVar1] = 0x60;
        DAT_00ff6094 = *(undefined2 *)((int)&DAT_00ffe792 + iVar1);
        DAT_00ff6096 = *(undefined2 *)((int)&DAT_00ffe79e + iVar1);
        DAT_00ff609a = 0x60;
        DAT_00ff609d = 1;
        DAT_00ff6152 = *(ushort *)((int)&DAT_00ffe79e + iVar1) >> 3;
        DAT_00ff6098 = DAT_00ff6152 + *(short *)((int)&DAT_00ffe792 + iVar1);
        if (*(ushort *)((int)&DAT_00ffe79e + iVar1) < DAT_00ff6098) {
          DAT_00ff6098 = *(ushort *)((int)&DAT_00ffe79e + iVar1);
        }
        *(ushort *)((int)&DAT_00ffe792 + iVar1) = DAT_00ff6098;
        DAT_00ff60a4 = 0xd;
        DAT_00ff60a6 = 0x10;
        DAT_00ff60a0 = 0;
        DAT_00ff60a2 = 0x1c;
        Seed_e50();
        FUN_00027f48();
        FUN_00001098();
        FUN_00009c4a();
        DAT_00ff60aa = 0xff;
        DAT_00ff60ab = 7;
        DAT_00ff6085 = 6;
      }
    }
    else {
      FUN_0000b854();
      DAT_00ff6085 = 0x12;
    }
  }
  return;
}

