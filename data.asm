.include "hdr.asm"

.section ".rodata1" superfree

logoMode7Pic:
.incbin "res/mode7.pc7"
logoMode7Pic_end:

logoMode7TileMap:
.incbin "res/mode7.mp7"
logoMode7TileMap_end:

logoMode7Palette:
.incbin "res/mode7.pal"

.ends

.section ".rodata2" superfree

logoMode5Pic:
.incbin "res/mode5.pic"
logoMode5Pic_end:

logoMode5Palette:
.incbin "res/mode5.pal"
logoMode5Palette_end:

.ends
