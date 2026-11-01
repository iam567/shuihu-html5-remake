/* Ghidra 12.1.4 pseudocode, not original source. ROM address 00003142 */

undefined8 FUN_00003142(void)

{
  int iVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  undefined2 *unaff_A2;
  
  iVar1 = (uint)(ushort)((short)in_D0 * 2 + (short)in_D1 * 0x80) * 0x10000;
  Ram00c00004 = iVar1 + 0x60000003;
  Ram00c00000 = *unaff_A2;
  Ram00c00000 = unaff_A2[1];
  Ram00c00000 = unaff_A2[2];
  Ram00c00000 = unaff_A2[3];
  Ram00c00004 = iVar1 + 0x60800003;
  Ram00c00000 = unaff_A2[4];
  Ram00c00000 = unaff_A2[5];
  Ram00c00000 = unaff_A2[6];
  Ram00c00000 = unaff_A2[7];
  Ram00c00004 = iVar1 + 0x61000003;
  Ram00c00000 = unaff_A2[8];
  Ram00c00000 = unaff_A2[9];
  Ram00c00000 = unaff_A2[10];
  Ram00c00000 = unaff_A2[0xb];
  Ram00c00004 = iVar1 + 0x61800003;
  Ram00c00000 = unaff_A2[0xc];
  Ram00c00000 = unaff_A2[0xd];
  Ram00c00000 = unaff_A2[0xe];
  Ram00c00000 = unaff_A2[0xf];
  return CONCAT44(in_D0,in_D1);
}

