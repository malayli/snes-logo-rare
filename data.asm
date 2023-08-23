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
logoMode7Palette_end:

.ends

.section ".rodata2" superfree

logoMode5Pic:
.incbin "res/mode5.pic"
logoMode5Pic_end:

logoMode5Palette:
.incbin "res/mode5.pal"
logoMode5Palette_end:

.ends

.section ".rodata3" superfree

logoMode3Bg2Pic:
.incbin "res/mode3bg2.pic"
logoMode3Bg2Pic_end:

logoMode3Bg2Palette:
.incbin "res/mode3bg2.pal"
logoMode3Bg2Palette_end:

.ends

.section ".rodata4" superfree

logoMode3Bg1Pic:
.incbin "res/mode3bg1.pic"
logoMode3Bg1Pic_end:

logoMode3Bg1Palette:
.incbin "res/mode3bg1.pal"
logoMode3Bg1Palette_end:

.ends
