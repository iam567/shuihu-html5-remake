/* Ghidra 12.1.4 pseudocode, not original source. ROM address 001e3a00 */

undefined8 FUN_001e3a00(void)

{
  byte bVar1;
  undefined4 in_D0;
  short sVar2;
  undefined4 in_D1;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  Ram00a11100 = 0x100;
  Ram00a11200 = 0x100;
  do {
    bVar1 = DAT_00a11100;
  } while ((bVar1 & 1) != 0);
  puVar3 = &DAT_001e3b02;
  puVar4 = &DAT_00a00000;
  sVar2 = DAT_001e3b00;
  do {
    *puVar4 = *puVar3;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  } while (sVar2 != -1);
  Ram00a11200 = 0;
  Ram00a11100 = 0;
  Ram00a11200 = 0x100;
  return CONCAT44(in_D0,in_D1);
}

