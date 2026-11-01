/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0000ba5c */

undefined8 FUN_0000ba5c(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  undefined2 *unaff_A2;
  undefined2 *puVar2;
  
  Ram00c00004 = CONCAT31((uint3)(((uint)(ushort)((short)in_D0 << 5) << 0x12) >> 10),
                         ((byte)((uint)in_D0 >> 8) & 7) >> 1) | 0x40000000;
  sVar1 = (short)in_D1 + -1;
  do {
    Ram00c00000 = *unaff_A2;
    Ram00c00000 = unaff_A2[1];
    Ram00c00000 = unaff_A2[2];
    Ram00c00000 = unaff_A2[3];
    Ram00c00000 = unaff_A2[4];
    Ram00c00000 = unaff_A2[5];
    Ram00c00000 = unaff_A2[6];
    Ram00c00000 = unaff_A2[7];
    Ram00c00000 = unaff_A2[8];
    Ram00c00000 = unaff_A2[9];
    Ram00c00000 = unaff_A2[10];
    Ram00c00000 = unaff_A2[0xb];
    Ram00c00000 = unaff_A2[0xc];
    Ram00c00000 = unaff_A2[0xd];
    puVar2 = unaff_A2 + 0xf;
    Ram00c00000 = unaff_A2[0xe];
    unaff_A2 = unaff_A2 + 0x10;
    Ram00c00000 = *puVar2;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return CONCAT44(in_D0,in_D1);
}

