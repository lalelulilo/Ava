/* In-Game Console */

#include "BearLibTerminal.h"
#include "console.h"

static int runConsole = 0;

/* Start the console loop */
int console_start() {
    int prevLayer = terminal_state( TK_LAYER );

    terminal_clear();
    terminal_layer( LAYER_CONSOLE );

    terminal_print( 0, 0, "Oh no!" );
    terminal_refresh();

    runConsole = 1;
    while ( runConsole ) {
        switch ( terminal_read() ) {
        case TK_GRAVE:
            /* Stop the console loop */
            runConsole = 0;
            break;
        default:
            break;
        }
    }

    /* Return to the layer that the caller was at */
    /* TODO(tszucs): Terminal clear area */
    terminal_clear();
    terminal_layer( prevLayer );

    return 0;
}
