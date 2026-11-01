002C3A 48e7fc20                 movem.l    d0-d5/a2, -(a7)
002C3E 4eb900003074             jsr        $3074.l
002C44 13da00ffe106             move.b     (a2)+, $ffe106.l
002C4A 13da00ffe107             move.b     (a2)+, $ffe107.l
002C50 13da00ffe108             move.b     (a2)+, $ffe108.l
002C56 13da00ffe109             move.b     (a2)+, $ffe109.l
002C5C 13da00ffe104             move.b     (a2)+, $ffe104.l
002C62 13da00ffe105             move.b     (a2)+, $ffe105.l
002C68 33da00ffe002             move.w     (a2)+, $ffe002.l
002C6E 33da00ffe004             move.w     (a2)+, $ffe004.l
002C74 13da00ffe006             move.b     (a2)+, $ffe006.l
002C7A 13da00ffe001             move.b     (a2)+, $ffe001.l
002C80 13da00ffe10a             move.b     (a2)+, $ffe10a.l
002C86 13da00ffe10b             move.b     (a2)+, $ffe10b.l
002C8C 13da00ffe10c             move.b     (a2)+, $ffe10c.l
002C92 4245                     clr.w      d5
002C94 1a3900ffe104             move.b     $ffe104.l, d5
002C9A 6a00000c                 bpl.w      $2ca8
002C9E 4405                     neg.b      d5
002CA0 eb4d                     lsl.w      #$5, d5
002CA2 4445                     neg.w      d5
002CA4 60000004                 bra.w      $2caa
002CA8 eb4d                     lsl.w      #$5, d5
002CAA 33c500ff6014             move.w     d5, $ff6014.l
002CB0 4245                     clr.w      d5
002CB2 1a3900ffe105             move.b     $ffe105.l, d5
002CB8 6a00000c                 bpl.w      $2cc6
002CBC 4405                     neg.b      d5
002CBE eb4d                     lsl.w      #$5, d5
002CC0 4445                     neg.w      d5
002CC2 60000004                 bra.w      $2cc8
002CC6 eb4d                     lsl.w      #$5, d5
002CC8 33c500ff6016             move.w     d5, $ff6016.l
002CCE 423900ff6034             clr.b      $ff6034.l
002CD4 423900ff6035             clr.b      $ff6035.l
002CDA 427900ff6008             clr.w      $ff6008.l
002CE0 427900ff600a             clr.w      $ff600a.l
002CE6 427900ff600c             clr.w      $ff600c.l
002CEC 427900ff600e             clr.w      $ff600e.l
002CF2 13fc000100ff603a         move.b     #$1, $ff603a.l
002CFA 4cdf043f                 movem.l    (a7)+, d0-d5/a2
002CFE 4e75                     rts        
002D00 48e7e038                 movem.l    d0-d2/a2-a4, -(a7)
002D04 323900ffe100             move.w     $ffe100.l, d1
002D0A 3401                     move.w     d1, d2
002D0C e049                     lsr.w      #$8, d1
002D0E 024200ff                 andi.w     #$ff, d2
002D12 45f9000dd744             lea.l      $dd744.l, a2
002D18 e549                     lsl.w      #$2, d1
002D1A 24721000                 movea.l    (a2, d1.w), a2
002D1E e54a                     lsl.w      #$2, d2
002D20 24722000                 movea.l    (a2, d2.w), a2
002D24 303c001f                 move.w     #$1f, d0
002D28 323c0000                 move.w     #$0, d1
002D2C 4eb900002d38             jsr        $2d38.l
002D32 4cdf1c07                 movem.l    (a7)+, d0-d2/a2-a4
002D36 4e75                     rts        
002D38 48e70018                 movem.l    a3-a4, -(a7)
002D3C 33fc813400c00004         move.w     #$8134, $c00004.l
002D44 23fcc000000000c00004     move.l     #$c0000000, $c00004.l
002D4E 47f900ffef00             lea.l      $ffef00.l, a3
002D54 49f900ffef80             lea.l      $ffef80.l, a4
002D5A e349                     lsl.w      #$1, d1
002D5C d6c1                     adda.w     d1, a3
002D5E d8c1                     adda.w     d1, a4
002D60 33fc000000c00000         move.w     #$0, $c00000.l
002D68 38fc0000                 move.w     #$0, (a4)+
002D6C 36da                     move.w     (a2)+, (a3)+
002D6E 51c8fff0                 dbra       d0, $2d60
002D72 33fc817400c00004         move.w     #$8174, $c00004.l
002D7A 4cdf1800                 movem.l    (a7)+, a3-a4
002D7E 4e75                     rts        
002D80 48e7e030                 movem.l    d0-d2/a2-a3, -(a7)
002D84 4eb900001098             jsr        $1098.l
002D8A 4eb9000010ac             jsr        $10ac.l
002D90 4eb900002e38             jsr        $2e38.l
002D96 47f900ffb000             lea.l      $ffb000.l, a3
002D9C 4207                     clr.b      d7
002D9E 4eb900002dc6             jsr        $2dc6.l
002DA4 47f900ffc000             lea.l      $ffc000.l, a3
002DAA 4207                     clr.b      d7
002DAC 4eb900002dc6             jsr        $2dc6.l
002DB2 47f900ffd000             lea.l      $ffd000.l, a3
002DB8 4207                     clr.b      d7
002DBA 4eb900002dc6             jsr        $2dc6.l
002DC0 4cdf0c07                 movem.l    (a7)+, d0-d2/a2-a3
002DC4 4e75                     rts        
002DC6 121a                     move.b     (a2)+, d1
002DC8 0c0100f0                 cmpi.b     #$f0, d1
002DCC 66000008                 bne.w      $2dd6
002DD0 1e3c0000                 move.b     #$0, d7
002DD4 60f0                     bra.b      $2dc6
002DD6 0c0100f1                 cmpi.b     #$f1, d1
002DDA 66000008                 bne.w      $2de4
002DDE 1e3c0001                 move.b     #$1, d7
002DE2 60e2                     bra.b      $2dc6
002DE4 0c0100ef                 cmpi.b     #$ef, d1
002DE8 62000006                 bhi.w      $2df0
002DEC 16c1                     move.b     d1, (a3)+
002DEE 60d6                     bra.b      $2dc6
002DF0 0c0100ff                 cmpi.b     #$ff, d1
002DF4 6700000a                 beq.w      $2e00
002DF8 0201000f                 andi.b     #$f, d1
002DFC 6000000c                 bra.w      $2e0a
002E00 121a                     move.b     (a2)+, d1
002E02 0c010000                 cmpi.b     #$0, d1
002E06 6700002e                 beq.w      $2e36
002E0A 0c070000                 cmpi.b     #$0, d7
002E0E 67000016                 beq.w      $2e26
002E12 4240                     clr.w      d0
002E14 5301                     subq.b     #$1, d1
002E16 1001                     move.b     d1, d0
002E18 121a                     move.b     (a2)+, d1
002E1A 141a                     move.b     (a2)+, d2
002E1C 16c1                     move.b     d1, (a3)+
002E1E 16c2                     move.b     d2, (a3)+
002E20 51c8fffa                 dbra       d0, $2e1c
002E24 60a0                     bra.b      $2dc6
002E26 4240                     clr.w      d0
002E28 5301                     subq.b     #$1, d1
002E2A 1001                     move.b     d1, d0
002E2C 121a                     move.b     (a2)+, d1
002E2E 16c1                     move.b     d1, (a3)+
002E30 51c8fffc                 dbra       d0, $2e2e
002E34 6090                     bra.b      $2dc6
002E36 4e75                     rts        
002E38 45f9000293ea             lea.l      $293ea.l, a2
002E3E 323900ffe100             move.w     $ffe100.l, d1
002E44 3401                     move.w     d1, d2
002E46 024200ff                 andi.w     #$ff, d2
002E4A e049                     lsr.w      #$8, d1
002E4C e549                     lsl.w      #$2, d1
002E4E 24721000                 movea.l    (a2, d1.w), a2
002E52 e54a                     lsl.w      #$2, d2
002E54 24722000                 movea.l    (a2, d2.w), a2
002E58 4e75                     rts        
002E5A 48e76000                 movem.l    d1-d2, -(a7)
002E5E 323900ffe100             move.w     $ffe100.l, d1
002E64 3401                     move.w     d1, d2
002E66 e049                     lsr.w      #$8, d1
002E68 024200ff                 andi.w     #$ff, d2
002E6C 45f9000770a6             lea.l      $770a6.l, a2
002E72 e549                     lsl.w      #$2, d1
002E74 24721000                 movea.l    (a2, d1.w), a2
002E78 e54a                     lsl.w      #$2, d2
002E7A 24722000                 movea.l    (a2, d2.w), a2
002E7E 4cdf0006                 movem.l    (a7)+, d1-d2
002E82 4e75                     rts        
002E84 48e7e030                 movem.l    d0-d2/a2-a3, -(a7)
002E88 4eb900000e40             jsr        $e40.l
002E8E 4eb900002ea6             jsr        $2ea6.l
002E94 203c00000200             move.l     #$200, d0
002E9A 4eb900000e50             jsr        $e50.l
002EA0 4cdf0c07                 movem.l    (a7)+, d0-d2/a2-a3
002EA4 4e75                     rts        
002EA6 323900ffe100             move.w     $ffe100.l, d1
002EAC 3401                     move.w     d1, d2
002EAE e049                     lsr.w      #$8, d1
002EB0 024200ff                 andi.w     #$ff, d2
002EB4 45f900032182             lea.l      $32182.l, a2
002EBA e549                     lsl.w      #$2, d1
002EBC 24721000                 movea.l    (a2, d1.w), a2
002EC0 e54a                     lsl.w      #$2, d2
002EC2 24722000                 movea.l    (a2, d2.w), a2
002EC6 4e75                     rts        
