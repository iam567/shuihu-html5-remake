/* Ghidra 12.1.4 pseudocode, not original source. ROM address 0001a552 */

void FUN_0001a552(void)

{
  byte bVar1;
  short sVar2;
  undefined1 *puVar3;
  
  sVar2 = (DAT_00ffe100 >> 8) << 2;
  puVar3 = (undefined1 *)
           ((int)(short)((DAT_00ffe100 & 0xff) << 1) + *(int *)(&DAT_000dc72e + sVar2));
  DAT_00ff6018 = *puVar3;
  bVar1 = puVar3[1];
  DAT_00ff610e = (char)(CONCAT11((char)((ushort)sVar2 >> 8),bVar1) >> 4);
  DAT_00ff610d = bVar1 & 0xf;
  return;
}

