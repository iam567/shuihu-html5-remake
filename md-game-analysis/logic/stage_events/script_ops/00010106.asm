00010106  move.l A3,(0x00ff6130).l  ; len 6
0001010c  bset.b #0x2,(0x00ff6019).l  ; len 8
00010114  bclr.b #0x1,(0x00ff603d).l  ; len 8
0001011c  rts  ; len 2
