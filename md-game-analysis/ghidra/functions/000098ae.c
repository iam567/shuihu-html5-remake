/* Ghidra 12.1.4 pseudocode, not original source. ROM address 000098ae */

void FUN_000098ae(void)

{
  short sVar1;
  short sVar2;
  char cVar3;
  short unaff_D3w;
  char *pcVar4;
  
  sVar2 = 0xc;
  sVar1 = 0x11;
  if (DAT_00ffe1f7 != '\x02') {
    sVar2 = 0;
    sVar1 = 0xb;
  }
  cVar3 = (char)sVar2;
  pcVar4 = (char *)((int)&DAT_00ffe780 + (int)(short)(sVar2 << 6));
  do {
    if ((*pcVar4 != '\0') && (cVar3 != DAT_00ff606b)) {
      sVar1 = FUN_00006902();
      (&DAT_00ff5000)[unaff_D3w] = 0xff;
    }
    cVar3 = cVar3 + '\x01';
    pcVar4 = pcVar4 + 0x40;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return;
}

