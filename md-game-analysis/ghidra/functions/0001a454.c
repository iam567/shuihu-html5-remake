/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001a454 */

void FUN_0001a454(void)

{
  short sVar1;
  short sVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  char *pcVar5;
  char *pcVar6;
  undefined2 *puVar7;
  undefined1 *puVar8;
  
  sVar1 = 0x7f;
  puVar3 = &DAT_00ffe400;
  puVar4 = &DAT_00ffe480;
  puVar7 = &DAT_00ffa000;
  puVar8 = &DAT_00ff1000;
  do {
    *(undefined1 *)puVar7 = *puVar3;
    *puVar3 = 0;
    *puVar8 = *puVar4;
    *puVar4 = 0;
    sVar1 = sVar1 + -1;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
    puVar7 = (undefined2 *)((int)puVar7 + 1);
    puVar8 = puVar8 + 1;
  } while (sVar1 != -1);
  sVar1 = 0;
  sVar2 = 0x7f;
  puVar3 = &DAT_00ffe400;
  pcVar5 = &DAT_00ffe480;
  do {
    puVar4 = puVar3;
    pcVar6 = pcVar5;
    if ((*(char *)((int)&DAT_00ffa000 + (int)sVar1) != '\0') && ((&DAT_00ff1000)[sVar1] != '\0')) {
      pcVar6 = pcVar5 + 1;
      *pcVar5 = (&DAT_00ff1000)[sVar1];
      puVar4 = puVar3 + 1;
      *puVar3 = *(undefined1 *)((int)&DAT_00ffa000 + (int)sVar1);
    }
    sVar1 = sVar1 + 1;
    sVar2 = sVar2 + -1;
    puVar3 = puVar4;
    pcVar5 = pcVar6;
  } while (sVar2 != -1);
  return;
}

