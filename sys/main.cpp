/* Entry point for AVA */

/* Note(tszucs): This allows us to start from main() instead of WinMain().. */
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "BearLibTerminal.h"
#include "console.h"
#include "debug.h"
#include "input.h"


/* Conditional for main game loop */
static int runGame = 1;

int main() {
    Console debugConsole( LAYER_DEBUG_CONSOLE );
	InputHandler input;


    /* Create our main window */
    if ( !terminal_open() ) {
        AVA_ERROR( "Failed to open terminal window.. exiting\n" );
        return -1;
    }

    /* Terminal settings */
    if ( !terminal_set( "window: title='AVA', size=200x50" ) ) {
        AVA_ERROR( "Failed to set window title and size... exiting\n" );
        return -1;
    }
    if ( !terminal_set( "font: ./NotoMono-Regular.ttf, size=11" ) ) {
        AVA_ERROR( "Failed to set terminal font.. exiting\n" );
        return -1;
    }

    while ( runGame ) {
        terminal_refresh();

        /* TODO(tszucs): Deal with key releases being read */
        switch (input.readInput()){
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
