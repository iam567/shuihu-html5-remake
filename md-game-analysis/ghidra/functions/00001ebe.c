/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00001ebe */

void FUN_00001ebe(void)

{
  char cVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short *unaff_A2;
  char *pcVar6;
  
  pcVar6 = &DAT_00ffe080;
  sVar5 = 0;
  sVar4 = 7;
  do {
    if (((*pcVar6 != '\0') && (sVar2 = *(short *)(pcVar6 + 2) - DAT_00ff6014, sVar2 < 0x141)) &&
       (-0x21 < sVar2)) {
      sVar3 = *(short *)(pcVar6 + 4) - DAT_00ff6016;
      if ((sVar3 < 0xf1) && (-0x21 < sVar3)) {
        *unaff_A2 = sVar2 + 0x80;
        unaff_A2[1] = sVar3 + 0x80;
        if (DAT_00ff6031 == '\0') {
          cVar1 = pcVar6[6];
          if (cVar1 == '\0') {
            pcVar6[1] = '\0';
LAB_00001f68:
            pcVar6[1] = (((byte)DAT_00ff6010 & 0x30) >> 4) + pcVar6[1];
          }
          else {
            if (cVar1 == '\x01') {
              pcVar6[1] = '\x04';
              goto LAB_00001f68;
            }
            if (cVar1 == '\x02') {
              pcVar6[1] = '\b';
              goto LAB_00001f68;
            }
            if (cVar1 == '\x03') {
              pcVar6[1] = '\f';
              goto LAB_00001f68;
            }
          }
          DAT_00ff601e._0_1_ = DAT_00ff601e._0_1_ | 1;
        }
        unaff_A2[2] = *(short *)(*(int *)((int)&DAT_00001fae + (int)sVar5) +
                                (int)(short)((ushort)(byte)pcVar6[1] << 1));
        DAT_00ff6012 = DAT_00ff6012 + 1;
        unaff_A2 = unaff_A2 + 3;
      }
    }
    sVar5 = sVar5 + 4;
    pcVar6 = pcVar6 + 0x10;
    sVar4 = sVar4 + -1;
    if (sVar4 == -1) {
      return;
    }
  } while( true );
}

