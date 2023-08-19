.include "hdr.asm"

.section ".rodata1" superfree

logoPic:
.incbin "res/logo.pc7"
logoPic_end:

logoMap:
.incbin "res/logo.mp7"
logoMap_end:

logoPalette:
.incbin "res/logo.pal"

.ends

.section ".rodata2" superfree

mode5Pic:
.incbin "res/mode5.pic"
mode5Pic_end:

mode5Palette:
.incbin "res/mode5.pal"
mode5Palette_end:

.ends
