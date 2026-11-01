000103ce  move.l A3,(0x00ff6130).l  ; len 6
000103d4  clr.b (0x00ff6158).l  ; len 6
000103da  lea (0xffe780).l,A2  ; len 6
000103e0  clr.b D1b  ; len 2
000103e2  move.w #0x1d,D0w  ; len 4
000103e6  tst.b (0x2f,A2)  ; len 4
000103ea  bne.w 0x00010402  ; len 4
000103ee  addq.b #0x1,D1b  ; len 2
000103f0  adda.w #0x40,A2  ; len 4
000103f4  dbf D0w,0x000103e6  ; len 4
000103f8  clr.b (0x00ff6159).l  ; len 6
000103fe  bra.w 0x00010414  ; len 4
00010402  clr.b (0x2f,A2)  ; len 4
00010406  move.b D1b,(0x00ff6150).l  ; len 6
0001040c  move.b #0x1,(0x00ff6158).l  ; len 8
00010414  rts  ; len 2
