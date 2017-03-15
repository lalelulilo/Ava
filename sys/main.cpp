/* Entry point for AVA */

/* Note(tszucs): This allows us to start from main() instead of WinMain().. */
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "BearLibTerminal.h"
#include "console.h"
#include "debug.h"

/* Conditional for main game loop */
static int runGame = 1;

int main() {
    Console debugConsole( 255 );

    /* Create our main window */
    if ( !terminal_open() ) {
        LOG( VERBOSITY_SYS, "Failed to open terminal window.. exiting\n" );
        return -1;
    }

    /* Terminal settings */
    if ( !terminal_set( "window: title='AVA', size=200x50" ) ) {
        LOG( VERBOSITY_SYS, "Failed to set window title and size... exiting\n" );
        return -1;
    }
    if ( !terminal_set( "font: ./NotoMono-Regular.ttf, size=11" ) ) {
        LOG( VERBOSITY_SYS, "Failed to set terminal font.. exiting\n" );
        return -1;
    }

    LOG( VERBOSITY_SYS, "Waiting for terminal to be closed..\n" );
    while ( runGame ) {
        terminal_print( 0, 0, "Oh yeah!" );
        terminal_print( 0, 1, "You gotta get schwifty" );
        terminal_print( 0, 2, "You gotta get schwifty in here" );
        terminal_print( 0, 3, "It's time to get schwifty" );
        terminal_refresh();

        /* TODO(tszucs): Deal with key releases being read */
        switch ( terminal_read() ) {
        case TK_GRAVE:
            debugConsole.show();
            break;
        case TK_CLOSE:
            runGame = 0;
            break;
        default:
            break;
        }
    }

    terminal_close();

    return 0;
}
