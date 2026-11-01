/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000124f8 */

void FUN_000124f8(void)

{
  short sVar1;
  undefined1 *puVar2;
  
  if (DAT_00ff6085 == '\0') {
    puVar2 = &DAT_00ffea80;
    sVar1 = 0x17;
    do {
      if ((*(undefined **)(puVar2 + 2) == &DAT_00a00020) || (*(int *)(puVar2 + 2) == 0xc00040))
      goto LAB_00012544;
      puVar2 = puVar2 + 0x40;
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    if (DAT_00ffe780._0_1_ == '\0') {
      if (DAT_00ff6310 != '\0') {
        return;
      }
LAB_00012544:
      FUN_00014144();
      return;
    }
  }
  if (DAT_00ffe1f5 == -1) {
    if ((DAT_00ff6019 & 2) == 0) {
      DAT_00ffe1f5 = '\0';
      FUN_00014144();
    }
  }
  else if (DAT_00ffea80 == '\0') {
    if ((DAT_00ff6310 == '\0') && ((DAT_00ff614f & 1) == 0)) {
      FUN_00014144();
    }
  }
  else if ((((DAT_00ffe1fc & 2) == 0) && (DAT_00ffea92 == 0)) && (DAT_00ff609a == '\0')) {
    DAT_00ff6019 = DAT_00ff6019 & 0xfb;
    DAT_00ffe1fc = DAT_00ffe1fc | 2;
    FUN_00014144();
  }
  return;
}

