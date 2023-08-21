/*---------------------------------------------------------------------------------


    Rare Logo for SNES Projects


---------------------------------------------------------------------------------*/
#include <snes.h>
#include "soundbank.h"

// ROM

#define PAL0 0
#define PAL1 1
#define PAL2 2
#define PAL3 3
#define PAL4 4
#define PAL5 5
#define PAL6 6
#define PAL7 7

#define TPAL0 PAL0<<10
#define TPAL1 PAL1<<10
#define TPAL2 PAL2<<10
#define TPAL3 PAL3<<10
#define TPAL4 PAL4<<10

#define BG0 0
#define BG1 1
#define BG2 2
#define BG3 3
#define BG4 4

extern char logoPic, logoPic_end;
extern char logoPalette;
extern char logoMap, logoMap_end;

extern char mode5Pic, mode5Pic_end;
extern char mode5Palette;

// RAM

u16 logoScale;
u8 logoState;
u16 framesCounter;
u16 sx;
u16 sy;

const u16 logoTileMap[] = {
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0,
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0,
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 

// Nintendo logo
00 | TPAL0, 02 | TPAL0, 04 | TPAL4, 06 | TPAL4, 8 | TPAL4, 10 | TPAL4, 12 | TPAL4, 14 | TPAL3, 16 | TPAL2, 18 | TPAL3, 20 | TPAL3, 22 | TPAL4, 24 | TPAL3, 26 | TPAL3, 28 | TPAL3, 30 | TPAL3, 32 | TPAL2, 34 | TPAL3, 36 | TPAL4, 38 | TPAL4, 40 | TPAL4, 42 | TPAL4, 44 | TPAL4, 46 | TPAL4, 48 | TPAL4, 50 | TPAL4, 52 | TPAL3, 54 | TPAL3, 56 | TPAL3, 58 | TPAL4, 60 | TPAL0, 0 | TPAL0, 
64 | TPAL0, 66 | TPAL4, 68 | TPAL4, 70 | TPAL4, 72 | TPAL4, 74 | TPAL4, 76 | TPAL4, 78 | TPAL4, 80 | TPAL4, 82 | TPAL4, 84 | TPAL4, 86 | TPAL4, 88 | TPAL4, 90 | TPAL4, 92 | TPAL4, 94 | TPAL4, 96 | TPAL4, 98 | TPAL4, 100 | TPAL4, 102 | TPAL4, 104 | TPAL4, 106 | TPAL4, 108 | TPAL4, 110 | TPAL4, 112 | TPAL4, 114 | TPAL2, 116 | TPAL2, 118 | TPAL2, 120 | TPAL2, 122 | TPAL2, 124 | TPAL4, 0 | TPAL0, 
128 | TPAL0, 130 | TPAL4, 132 | TPAL4, 134 | TPAL4, 136 | TPAL4, 138 | TPAL4, 140 | TPAL4, 142 | TPAL4, 144 | TPAL2, 146 | TPAL2, 148 | TPAL2, 150 | TPAL2, 152 | TPAL3, 154 | TPAL3, 156 | TPAL3, 158 | TPAL2, 160 | TPAL2, 162 | TPAL2, 164 | TPAL2, 166 | TPAL2, 168 | TPAL2, 170 | TPAL2, 172 | TPAL2, 174 | TPAL2, 176 | TPAL2, 178 | TPAL2, 180 | TPAL2, 182 | TPAL2, 184 | TPAL2, 186 | TPAL2, 188 | TPAL4, 0 | TPAL0, 
192 | TPAL0, 194 | TPAL4, 196 | TPAL2, 198 | TPAL2, 200 | TPAL4, 202 | TPAL4, 204 | TPAL4, 206 | TPAL4, 208 | TPAL4, 210 | TPAL4, 212 | TPAL4, 214 | TPAL4, 216 | TPAL2, 218 | TPAL2, 220 | TPAL2, 222 | TPAL2, 224 | TPAL2, 226 | TPAL2, 228 | TPAL2, 230 | TPAL2, 232 | TPAL2, 234 | TPAL2, 236 | TPAL2, 238 | TPAL2, 240 | TPAL2, 242 | TPAL3, 244 | TPAL3, 246 | TPAL2, 248 | TPAL2, 250 | TPAL2, 252 | TPAL4, 0 | TPAL0, 
256 | TPAL0, 258 | TPAL2, 260 | TPAL2, 262 | TPAL2, 264 | TPAL4, 266 | TPAL4, 268 | TPAL4, 270 | TPAL4, 272 | TPAL4, 274 | TPAL4, 276 | TPAL4, 278 | TPAL3, 280 | TPAL3, 282 | TPAL2, 284 | TPAL2, 286 | TPAL2, 288 | TPAL2, 290 | TPAL2, 292 | TPAL2, 294 | TPAL2, 296 | TPAL4, 298 | TPAL4, 300 | TPAL4, 302 | TPAL4, 304 | TPAL4, 306 | TPAL2, 308 | TPAL4, 310 | TPAL3, 312 | TPAL3, 314 | TPAL3, 316 | TPAL4, 0 | TPAL0, 
320 | TPAL0, 322 | TPAL4, 324 | TPAL4, 326 | TPAL2, 328 | TPAL4, 330 | TPAL4, 332 | TPAL4, 334 | TPAL4, 336 | TPAL4, 338 | TPAL4, 340 | TPAL4, 342 | TPAL3, 344 | TPAL2, 346 | TPAL2, 348 | TPAL2, 350 | TPAL2, 352 | TPAL2, 354 | TPAL2, 356 | TPAL2, 358 | TPAL2, 360 | TPAL4, 362 | TPAL4, 364 | TPAL4, 366 | TPAL2, 368 | TPAL3, 370 | TPAL2, 372 | TPAL2, 374 | TPAL3, 376 | TPAL3, 378 | TPAL2, 380 | TPAL4, 0 | TPAL0,  
384 | TPAL0, 386 | TPAL4, 388 | TPAL4, 390 | TPAL4, 392 | TPAL2, 394 | TPAL4, 396 | TPAL4, 398 | TPAL4, 400 | TPAL4, 402 | TPAL4, 404 | TPAL4, 406 | TPAL4, 408 | TPAL2, 410 | TPAL2, 412 | TPAL2, 414 | TPAL2, 416 | TPAL2, 418 | TPAL2, 420 | TPAL2, 422 | TPAL2, 424 | TPAL2, 426 | TPAL4, 428 | TPAL4, 430 | TPAL4, 432 | TPAL4, 434 | TPAL4, 436 | TPAL4, 438 | TPAL3, 440 | TPAL4, 442 | TPAL4, 444 | TPAL0, 0 | TPAL0, 

0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 

// Presents
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 596 | TPAL2, 598 | TPAL2, 600 | TPAL2, 602 | TPAL2, 604 | TPAL2, 606 | TPAL2, 608 | TPAL2, 610 | TPAL2, 612 | TPAL2, 614 | TPAL2, 616 | TPAL2, 618 | TPAL2, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 660 | TPAL2, 662 | TPAL2, 664 | TPAL2, 666 | TPAL2, 668 | TPAL2, 670 | TPAL2, 672 | TPAL2, 674 | TPAL2, 676 | TPAL2, 678 | TPAL2, 680 | TPAL2, 682 | TPAL2, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 

0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0,

// Rareware logo
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | (PAL5<<10), 512 | (PAL5<<10), 514 | (PAL5<<10), 516 | (PAL5<<10), 518 | (PAL6<<10), 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | (PAL6<<10), 576 | (PAL6<<10), 578 | (PAL6<<10), 580 | (PAL6<<10), 582 | (PAL6<<10), 0 | TPAL0, 0 | TPAL0,
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | (PAL6<<10), 640 | (PAL6<<10), 642 | (PAL6<<10), 644 | (PAL6<<10), 646 | (PAL6<<10), 0 | TPAL0, 0 | TPAL0,
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | (PAL6<<10), 704 | (PAL6<<10), 706 | (PAL6<<10), 708 | (PAL6<<10), 710 | (PAL6<<10), 0 | TPAL0, 0 | TPAL0, 

0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 
0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0, 0 | TPAL0
};

// Macros

#define REG_MISC (*(vuint8 *)0x2133)
#define vblflip() { spcProcess();    WaitForVBlank(); }

/*!\brief Initialize the Rare logo screen in mode 7.
*/
void initRareLogoMode7() {
    logoState = 0;
    framesCounter = 0;

    // Read tiles & map to VRAM  (interlace for mode 7)
    bgInitMapTileSet7(&logoPic, &logoMap, &logoPalette, (&logoPic_end - &logoPic), 0x0000);

    // Now Put mode7 without anything else
    setMode7(0);

    bgSetScroll(0, 0, 0);

    // Set mode 7 map scale
    logoScale = 256;
    REG_M7A = logoScale;
    REG_M7A = logoScale>>8;
    REG_M7D = logoScale;
    REG_M7D = logoScale>>8;

    // Set mode 7 map {x,y} position
    sx = 261;
    sy = 215;
    REG_M7X = (sx) & 255;
    REG_M7X = (sx) >> 8;
    REG_M7Y = (sy) & 255;
    REG_M7Y = (sy) >> 8;
}

/*!\brief Initialize the Rare logo screen.
*/
void initRareLogo() {
    setBrightness(0); 

    initRareLogoMode7();

    // Load the mode 5 logo for loading time optimization
    bgInitTileSet(BG0, 
        &mode5Pic, 
        &mode5Palette, 
        PAL0, 
        (&mode5Pic_end - &mode5Pic), 
        32 * 7, 
        BG_16COLORS, 
        0x4000);

    // Set the mode 7 logo palette
    dmaCopyCGram(&logoPalette, PAL0, 32*2);

    setBrightness(0xF);
}

/*!\brief Update Rare logo animation.
    \return 1 when the logo animation is complete, 0 otherwise.
*/
u8 updateRareLogo() {
    switch(logoState) {
        case 0:
            if (framesCounter == 32) {
                logoState = 1;
            }
            break;

        case 1:
            if (logoScale < 880) {
                logoScale += 16;

                REG_M7A = logoScale; // Set the value in 1st byte
                REG_M7A = logoScale>>8; // Set the value in 2nd byte

                REG_M7D = logoScale; // Set the value in 1st byte
                REG_M7D = logoScale>>8; // Set the value in 2nd byte

            } else {
                logoState = 2;
                REG_BGMODE = BG_MODE5;
                REG_CGWSEL = 0b00000010;
                REG_TM = 0b00000001;
                REG_TS = 0b00000001;
                bgSetMapPtr(BG0, 0x7400, SC_32x32);
                dmaCopyVram((u8 *)logoTileMap, 0x7400, 32*32*2);
                dmaCopyCGram(&mode5Palette, PAL0, 32*7);
            }
            break;
        
        case 2:
            break;
    }

    framesCounter++;

    vblflip();

    return 0;
}
