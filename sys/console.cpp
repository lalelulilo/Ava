/* In-Game Console */

#include "BearLibTerminal.h"
#include "sys_local.h"

#define UNICODE_SQUARE    9608

Console::Console( int layerInit, int widthInit, int heightInit )
    : layer( layerInit ),
      width( widthInit ),
      height( heightInit ),
      runConsole( 0 )
{
    textBuf.size = 64;
    textBuf.dataSize = 128;
    textBuf.idx = 0;

    /* We should check if these mallocs don't go through... but where would we log to!?
       Not worth the headache as we will be allocating at most 1MB of memory */
    textBuf.text = (char**)malloc( textBuf.size * sizeof( textBuf ) );
    for ( int i = 0; i < textBuf.size; i++ ) {
        textBuf.text[i] = (char*)calloc( textBuf.dataSize, sizeof( textBuf.text[i] ) );
    }

    bgColor = color_from_argb( 0xFF, 0x1C, 0x1C, 0x1C );
    fgColor = color_from_argb( 0xFF, 0xFF, 0xFF, 0xFF );
}

Console::~Console() {
    for ( int i = 0; i < textBuf.size; i++ ) {
        free( textBuf.text[i] );
    }
    free( textBuf.text );
}

/* Show the console and start the loop */
void Console::show() {
    int currChar = 0;
    int prevLayer = terminal_state( TK_LAYER );
    color_t prevColor = (color_t)terminal_state( TK_COLOR );
    int prevComp = terminal_state( TK_COMPOSITION );

    /* We require composition for the terminal background */
    terminal_composition( TK_ON );

    /* Put a solid background across the entire layer */
    terminal_layer( layer - 1 );
    terminal_color( bgColor );
    for ( int i = 0; i < width; i++ ) {
        for ( int j = 0; j < height; j++ ) {
            terminal_put( i, j, UNICODE_SQUARE );
        }
    }

    terminal_layer( layer );
    terminal_color( fgColor );

    terminal_print( 0, 0, "Oh no!" );

    runConsole = 1;
    while ( runConsole ) {
        int i, key;

        /* Print all the previous text */
        terminal_clear_area( 0, 0, width, height );
        i = textBuf.idx;
        for ( int row = ( height - 1 ); row >= 0; row-- ) {
            terminal_print( 0, row, textBuf.text[i] );
            i--;
            if ( i < 0 ) {
                i = textBuf.size - 1;
            }
        }
        terminal_refresh();

        key = terminal_read();
        if ( key == TK_GRAVE || key == TK_CLOSE ) {
            /* Stop the console loop */
            runConsole = 0;
        } else if ( key == TK_ENTER ) {
            currChar = 0;
            textBuf.idx = ( textBuf.idx + 1 ) % textBuf.size;
        } else if ( key == TK_BACKSPACE && currChar >= 0 ) {
            if ( currChar > 0 ) currChar--;
            textBuf.text[textBuf.idx][currChar] = '\0';
        } else if ( terminal_check(TK_CHAR) &&
                    currChar < textBuf.dataSize &&
                    currChar < width ) {
            textBuf.text[textBuf.idx][currChar] = (char)terminal_state( TK_CHAR );
            if ( currChar < ( textBuf.dataSize - 1 ) ) currChar++;
        }
    }

    /* Return to the layer that the caller was at */
    terminal_clear_area( 0, 0, width, height );
    terminal_layer( layer - 1 );
    terminal_clear_area( 0, 0, width, height );

    /* Undo our state changes */
    terminal_layer( prevLayer );
    terminal_color( prevColor );
    terminal_composition( prevComp );
}
