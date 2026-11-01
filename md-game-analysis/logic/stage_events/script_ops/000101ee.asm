000101ee  move.w (A3)+,D1w  ; len 2
000101f0  move.l A3,(0x00ff6130).l  ; len 6
000101f6  lea (0xffe780).l,A2  ; len 6
000101fc  clr.w D2w  ; len 2
000101fe  move.b (0x00ff613e).l,D2b  ; len 6
00010204  lsl.w #0x6,D2w  ; len 2
00010206  move.b D1b,(0x0,A2,D2w*0x1)  ; len 4
