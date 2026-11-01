/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001977c */

uint FUN_0001977c(void)

{
  uint uVar1;
  short in_D0w;
  short in_D1w;
  short sVar2;
  undefined2 unaff_D2w;
  
  uVar1 = CONCAT31((uint3)(((uint)(ushort)(in_D0w << 5) << 0x12) >> 10),
                   ((byte)((ushort)in_D0w >> 8) & 7) >> 1) | 0x40000000;
  Ram00c00004 = uVar1;
  sVar2 = in_D1w + -1;
  do {
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    Ram00c00000 = unaff_D2w;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return uVar1;
}

