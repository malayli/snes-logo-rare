/*---------------------------------------------------------------------------------


    Rare Logo for SNES Projects


---------------------------------------------------------------------------------*/
#include <snes.h>
#include "soundbank.h"

// ROM

extern char logoPic, logoPic_end;
extern char logoPalette;
extern char logoMap, logoMap_end;

// RAM

u16 logoScale;
u8 logoState;
u16 framesCounter;
u16 sx;
u16 sy;

// Macro

#define vblflip() { spcProcess();    WaitForVBlank(); }

/*!\brief Initialize the Rare logo screen.
*/
void initRareLogo() {
    // Force VBlank
    setBrightness(0); 
    dmaClearVram(); 

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
                logoScale += 8;

                REG_M7A = logoScale; // Set the value in 1st byte
                REG_M7A = logoScale>>8; // Set the value in 2nd byte

                REG_M7D = logoScale; // Set the value in 1st byte
                REG_M7D = logoScale>>8; // Set the value in 2nd byte
            }
            break;
    }

    framesCounter++;

    vblflip();

    return 0;
}
