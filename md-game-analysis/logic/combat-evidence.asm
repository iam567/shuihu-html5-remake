005F9C 49f900ffe780             lea.l      $ffe780.l, a4
005FA2 4241                     clr.w      d1
005FA4 123900ff606b             move.b     $ff606b.l, d1
005FAA ed49                     lsl.w      #$6, d1
005FAC 16341018                 move.b     $18(a4, d1.w), d3
005FB0 4eb90000604e             jsr        $604e.l
005FB6 323900ff6100             move.w     $ff6100.l, d1
005FBC 0241003f                 andi.w     #$3f, d1
005FC0 c2fc0064                 mulu.w     #$64, d1
005FC4 ec49                     lsr.w      #$6, d1
005FC6 b203                     cmp.b      d3, d1
005FC8 62000010                 bhi.w      $5fda
005FCC 3002                     move.w     d2, d0
005FCE e248                     lsr.w      #$1, d0
005FD0 d440                     add.w      d0, d2
005FD2 13fc000200ff6103         move.b     #$2, $ff6103.l
005FDA 4e75                     rts        
005FDC 103c0000                 move.b     #$0, d0
005FE0 49f900ffe780             lea.l      $ffe780.l, a4
005FE6 4241                     clr.w      d1
005FE8 123900ff606b             move.b     $ff606b.l, d1
005FEE ed49                     lsl.w      #$6, d1
005FF0 14341019                 move.b     $19(a4, d1.w), d2
005FF4 49f900028e54             lea.l      $28e54.l, a4
005FFA 4241                     clr.w      d1
005FFC 123900ff60bc             move.b     $ff60bc.l, d1
006002 5301                     subq.b     #$1, d1
006004 e749                     lsl.w      #$3, d1
006006 d4341006                 add.b      $6(a4, d1.w), d2
00600A 49f900ffe780             lea.l      $ffe780.l, a4
006010 4241                     clr.w      d1
006012 123900ff609f             move.b     $ff609f.l, d1
006018 ed49                     lsl.w      #$6, d1
00601A 0c340000100c             cmpi.b     #$0, $c(a4, d1.w)
006020 66000026                 bne.w      $6048
006024 9434101a                 sub.b      $1a(a4, d1.w), d2
006028 65000022                 bcs.w      $604c
00602C 4eb90000604e             jsr        $604e.l
006032 323900ff6100             move.w     $ff6100.l, d1
006038 0241003f                 andi.w     #$3f, d1
00603C c2fc0064                 mulu.w     #$64, d1
006040 ec49                     lsr.w      #$6, d1
006042 b202                     cmp.b      d2, d1
006044 62000006                 bhi.w      $604c
006048 103c0001                 move.b     #$1, d0
00604C 4e75                     rts        
00604E 48e78000                 movem.l    d0, -(a7)
006052 303900ff6100             move.w     $ff6100.l, d0
006058 c0fc7fcf                 mulu.w     #$7fcf, d0
00605C 5680                     addq.l     #$3, d0
00605E 80fc7fed                 divu.w     #$7fed, d0
006062 4840                     swap       d0
006064 33c000ff6100             move.w     d0, $ff6100.l
00606A 4cdf0001                 movem.l    (a7)+, d0
00606E 4e75                     rts        
006070 47f900ffe780             lea.l      $ffe780.l, a3
006076 4241                     clr.w      d1
006078 123900ff606b             move.b     $ff606b.l, d1
00607E ed49                     lsl.w      #$6, d1
006080 4244                     clr.w      d4
006082 18331021                 move.b     $21(a3, d1.w), d4
006086 4242                     clr.w      d2
006088 14331014                 move.b     $14(a3, d1.w), d2
00608C 0c39000000ff60bb         cmpi.b     #$0, $ff60bb.l
006094 67000006                 beq.w      $609c
006098 14331015                 move.b     $15(a3, d1.w), d2
00609C 0c330000100e             cmpi.b     #$0, $e(a3, d1.w)
0060A2 67000004                 beq.w      $60a8
0060A6 e24a                     lsr.w      #$1, d2
0060A8 49f900028e54             lea.l      $28e54.l, a4
0060AE 4241                     clr.w      d1
0060B0 123900ff60bc             move.b     $ff60bc.l, d1
0060B6 5301                     subq.b     #$1, d1
0060B8 e749                     lsl.w      #$3, d1
0060BA 4243                     clr.w      d3
0060BC 16341000                 move.b     (a4, d1.w), d3
0060C0 d443                     add.w      d3, d2
0060C2 49f90000611e             lea.l      $611e.l, a4
0060C8 c8fc000f                 mulu.w     #$f, d4
0060CC d8c4                     adda.w     d4, a4
0060CE 4241                     clr.w      d1
0060D0 123900ff609f             move.b     $ff609f.l, d1
0060D6 ed49                     lsl.w      #$6, d1
0060D8 4244                     clr.w      d4
0060DA 18331021                 move.b     $21(a3, d1.w), d4
0060DE d8c4                     adda.w     d4, a4
0060E0 1814                     move.b     (a4), d4
0060E2 67000008                 beq.w      $60ec
0060E6 c4c4                     mulu.w     d4, d2
0060E8 84fc000a                 divu.w     #$a, d2
0060EC 4243                     clr.w      d3
0060EE 16331016                 move.b     $16(a3, d1.w), d3
0060F2 0c39000000ff60bb         cmpi.b     #$0, $ff60bb.l
0060FA 67000006                 beq.w      $6102
0060FE 16331017                 move.b     $17(a3, d1.w), d3
006102 0c330000100f             cmpi.b     #$0, $f(a3, d1.w)
006108 67000004                 beq.w      $610e
00610C e24b                     lsr.w      #$1, d3
00610E 9443                     sub.w      d3, d2
006110 0c420001                 cmpi.w     #$1, d2
006114 6c000006                 bge.w      $611c
006118 343c0001                 move.w     #$1, d2
00611C 4e75                     rts        
