/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00007982 */

undefined8 FUN_00007982(void)

{
  short sVar1;
  short sVar2;
  undefined4 in_D0;
  short sVar3;
  short sVar4;
  undefined4 in_D1;
  int unaff_A2;
  undefined1 *puVar5;
  
  DAT_00ff6037 = DAT_00ff6037 & 0xfe;
  sVar1 = *(short *)(unaff_A2 + 2);
  sVar2 = *(short *)(unaff_A2 + 4);
  sVar3 = FUN_000079fa();
  puVar5 = &DAT_00ffe080;
  sVar4 = 7;
  while ((((sVar4 == sVar3 || ((short)(*(short *)(puVar5 + 2) + 0x1f) <= sVar1)) ||
          (sVar1 <= (short)(*(short *)(puVar5 + 2) + -0x20))) ||
         (((short)(*(short *)(puVar5 + 4) + 0x1f) <= sVar2 ||
          (sVar2 <= (short)(*(short *)(puVar5 + 4) + -0x20)))))) {
    puVar5 = puVar5 + 0x10;
    sVar4 = sVar4 + -1;
    if (sVar4 == -1) {
LAB_000079f4:
      return CONCAT44(in_D0,in_D1);
    }
  }
  DAT_00ff6037 = DAT_00ff6037 | 1;
  goto LAB_000079f4;
}

