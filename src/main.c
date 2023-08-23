/*---------------------------------------------------------------------------------


    Rare Logo for SNES Projects


---------------------------------------------------------------------------------*/
#include <snes.h>
#include "logo.h"

int main(void) {
    // Initialize sound engine (take some time)
    spcBoot();

    // Initialize SNES
    consoleInit();

    dmaClearVram();

    initRareLogo();

    while (1) {
        if (updateRareLogo() == 1) {
            // The logo animation is complete
            // Paste your game code here
            // consoleNocashMessage("Start your game!");
        }
        
        spcProcess();
        
        WaitForVBlank();
    }
    return 0;
}
