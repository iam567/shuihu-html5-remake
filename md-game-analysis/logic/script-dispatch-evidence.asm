00FCA8 4a3900ff6030             tst.b      $ff6030.l
00FCAE 66000094                 bne.w      $fd44
00FCB2 0839000000ff603d         btst.b     #$0, $ff603d.l
00FCBA 67000088                 beq.w      $fd44
00FCBE 423900ff6036             clr.b      $ff6036.l
00FCC4 0839000100ff603d         btst.b     #$1, $ff603d.l
00FCCC 67000076                 beq.w      $fd44
00FCD0 267900ff6130             movea.l    $ff6130.l, a3
00FCD6 321b                     move.w     (a3)+, d1
00FCD8 0c41ffff                 cmpi.w     #$ffff, d1
00FCDC 6600003c                 bne.w      $fd1a
00FCE0 08b9000000ff603d         bclr.b     #$0, $ff603d.l
00FCE8 13fc000100ff6036         move.b     #$1, $ff6036.l
00FCF0 123900ffe1f6             move.b     $ffe1f6.l, d1
00FCF6 13c100ffe10e             move.b     d1, $ffe10e.l
00FCFC 13fc000200ffe10d         move.b     #$2, $ffe10d.l
00FD04 4a3900ffe116             tst.b      $ffe116.l
00FD0A 67000038                 beq.w      $fd44
00FD0E 13fc000400ffe10e         move.b     #$4, $ffe10e.l
00FD16 6000002c                 bra.w      $fd44
00FD1A 0c410fff                 cmpi.w     #$fff, d1
00FD1E 62b6                     bhi.b      $fcd6
00FD20 45f90000fd46             lea.l      $fd46.l, a2
00FD26 e549                     lsl.w      #$2, d1
00FD28 24721000                 movea.l    (a2, d1.w), a2
00FD2C 4e92                     jsr        (a2)
00FD2E 0839000000ff6157         btst.b     #$0, $ff6157.l
00FD36 6700000c                 beq.w      $fd44
00FD3A 08b9000000ff6157         bclr.b     #$0, $ff6157.l
00FD42 6092                     bra.b      $fcd6
00FD44 4e75                     rts        
