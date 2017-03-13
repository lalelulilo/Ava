/* Entry point for AVA */

/* Note(tszucs): This allows us to start from main() instead of WinMain().. */
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "BearLibTerminal.h"
#include "../havenlib/precompiled.h"

int main() {
    terminal_open();

    terminal_print( 0, 0, "Oh yeah!" );
    terminal_print( 0, 1, "You gotta get schwifty" );
    terminal_print( 0, 2, "You gotta get schwifty in here" );
    terminal_print( 0, 3, "It's time to get schwifty" );
    terminal_refresh();

    DebugPrintf( VERBOSITY_SYS, "Waiting for terminal to be closed..\n" );
    while ( terminal_read() != TK_CLOSE );

    terminal_close();
}
