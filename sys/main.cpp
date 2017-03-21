/* Entry point for AVA */

/* NOTE(tszucs): This allows us to start from main() instead of WinMain().. */
#ifdef _MSC_VER
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "BearLibTerminal.h"
#include "sys_local.h"

/* Global system state */
SysVars_t Sys = {
    "AVA",    // .title
    200,      // .screenWidth
    50,       // .screenHeight
};

static int runGame = 1;

int main() {
    Console debugConsole( LAYER_DEBUG_CONSOLE, Sys.screenWidth, Sys.screenHeight / 2 );

    /* Create our main window */
    if ( !terminal_open() ) {
        DEBUG_ERROR( "Failed to open terminal window.. exiting\n" );
        return -1;
    }

    /* Terminal settings */
    if ( !terminal_setf( "window: title='%s', size=%dx%d",
                         Sys.title, Sys.screenWidth, Sys.screenHeight ) ) {
        DEBUG_ERROR( "Failed to set window title and size... exiting\n" );
        return -1;
    }
    if ( !terminal_set( "font: ./NotoMono-Regular.ttf, size=11" ) ) {
        DEBUG_ERROR( "Failed to set terminal font.. exiting\n" );
        return -1;
    }


    DEBUG_LOG( VERBOSITY_SYS, "Launching main game loop\n" );
    terminal_color( color_from_argb( 0xFF, 0xFF, 0xFF, 0xFF ) );
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
