/* Entry point for AVA */

/* Note(tszucs): This allows us to start from main() instead of WinMain().. */
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "BearLibTerminal.h"
#include "../havenlib/precompiled.h"

/* Conditional for main game loop */
static bool runGame = true;

int main() {
    /* Create our main window */
    if ( !terminal_open() ) {
        DebugPrintf( VERBOSITY_SYS, "Failed to open terminal window.. exiting\n" );
        return -1;
    }

    /* Terminal settings */
    if ( !terminal_set( "window: title='AVA', size=200x50" ) ) {
        DebugPrintf( VERBOSITY_SYS, "Failed to set window title and size... exiting\n" );
        return -1;
    }
    if ( !terminal_set( "font: ./NotoMono-Regular.ttf, size=11" ) ) {
        DebugPrintf( VERBOSITY_SYS, "Failed to set terminal font.. exiting\n" );
        return -1;
    }

    terminal_print( 0, 0, "Oh yeah!" );
    terminal_print( 0, 1, "You gotta get schwifty" );
    terminal_print( 0, 2, "You gotta get schwifty in here" );
    terminal_print( 0, 3, "It's time to get schwifty" );
    terminal_refresh();

    DebugPrintf( VERBOSITY_SYS, "Waiting for terminal to be closed..\n" );
    while ( runGame ) {
        switch ( terminal_read() ) {
        case TK_CLOSE:
            runGame = false;
            break;
        default:
            break;
        }
    }

    terminal_close();

    return 0;
}
