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
