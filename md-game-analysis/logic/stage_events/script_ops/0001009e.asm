0001009e  move.l A3,(0x00ff6130).l  ; len 6
000100a4  move.b #0x2,(0x00ffe1f7).l  ; len 8
000100ac  move.b #0x1,(0x00ff6102).l  ; len 8
000100b4  move.l #0x0,(0x00ffe1e0).l  ; len 10
000100be  move.l #0x3fffffff,(0x00ff6080).l  ; len 10
000100c8  lea (0xffe780).l,A2  ; len 6
000100ce  move.w #0xb,D0w  ; len 4
000100d2  move.b #0x10,(0x1,A2)  ; len 6
000100d8  move.b #0x1,(0x6,A2)  ; len 6
000100de  adda.w #0x40,A2  ; len 4
000100e2  dbf D0w,0x000100d2  ; len 4
000100e6  lea (0xffea80).l,A2  ; len 6
000100ec  move.w #0x11,D0w  ; len 4
000100f0  move.b #0x11,(0x1,A2)  ; len 6
000100f6  move.b #0x1,(0x6,A2)  ; len 6
000100fc  adda.w #0x40,A2  ; len 4
00010100  dbf D0w,0x000100f0  ; len 4
00010104  rts  ; len 2
