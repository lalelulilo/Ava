/* In-Game Console */

#include "BearLibTerminal.h"
#include "console.h"

Console::Console( int layer )
{
    this->runConsole = 0;
    this->layer = layer;
}

/* Show the console and start the loop */
int Console::show() {
    int prevLayer = terminal_state( TK_LAYER );

    terminal_clear();
    terminal_layer( layer );

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
