/* In-Game Console */

#include "BearLibTerminal.h"
#include "sys_local.h"

#define UNICODE_SQUARE    9608

Console::Console( int layerInit, int widthInit, int heightInit )
    : layer( layerInit ),
      width( widthInit ),
      height( heightInit ),
      runConsole( 0 ),
      textBufferSize( 256 )
{
    textBuffer = (char*)malloc( textBufferSize * sizeof( textBuffer ) );
    DEBUG_ERROR_IF( textBuffer == NULL, "Failed to alloc mem for textBuffer" );

    bgColor = color_from_argb( 0xFF, 0x1C, 0x1C, 0x1C );
    fgColor = color_from_argb( 0xFF, 0xEB, 0xEB, 0xEB );
}

/* Show the console and start the loop */
void Console::show() {
    int prevLayer = terminal_state( TK_LAYER );
    color_t prevColor = (color_t)terminal_state( TK_COLOR );
    int prevComp = terminal_state( TK_COMPOSITION );

    /* We require composition for the terminal background */
    terminal_composition( TK_ON );

    /* Put a solid background across the entire layer */
    terminal_layer( layer );
    terminal_color( bgColor );
    for ( int i = 0; i < width; i++ ) {
        for ( int j = 0; j < height; j++ ) {
            terminal_put( i, j, UNICODE_SQUARE );
        }
    }
    terminal_color( fgColor );

    terminal_print( 0, 0, "Oh no!" );

    runConsole = 1;
    while ( runConsole ) {
        terminal_refresh();
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
    terminal_clear_area( 0, 0, width, height );

    /* Undo our state changes */
    terminal_layer( prevLayer );
    //terminal_color( prevColor );
    terminal_composition( prevComp );
}
