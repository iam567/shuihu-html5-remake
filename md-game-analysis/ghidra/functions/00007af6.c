/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007af6 */

undefined8 FUN_00007af6(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  char *pcVar5;
  
  DAT_00ff6037 = DAT_00ff6037 & 0xfe;
  uVar3 = DAT_00ffe002 >> 5;
  uVar4 = DAT_00ffe004 >> 5;
  FUN_00007ac2();
  pcVar5 = &DAT_00ffe080;
  sVar1 = 7;
  do {
    if (*pcVar5 != '\0') {
      uVar2 = *(ushort *)(pcVar5 + 2) >> 5;
      if ((uVar3 == uVar2) ||
         (((*(ushort *)(pcVar5 + 2) & 0x1f) != 0 && (uVar3 == (ushort)(uVar2 + 1))))) {
        uVar2 = *(ushort *)(pcVar5 + 4) >> 5;
        if ((uVar4 == uVar2) ||
           (((*(ushort *)(pcVar5 + 4) & 0x1f) != 0 && (uVar4 == (ushort)(uVar2 + 1))))) {
          DAT_00ff6037 = DAT_00ff6037 | 1;
          DAT_00ff606f = -((char)sVar1 + -7);
          goto LAB_00007b88;
        }
      }
    }
    pcVar5 = pcVar5 + 0x10;
    sVar1 = sVar1 + -1;
    if (sVar1 == -1) {
LAB_00007b88:
      return CONCAT44(in_D0,in_D1);
    }
  } while( true );
}

