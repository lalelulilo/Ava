/* Debug Functions */

#include <stdarg.h>
#include <stdio.h>

#include <windows.h>

#include "debug.h"

static int verbosityMask = VERBOSITY_SYS;

void vLog( const int verbosity, const char *fmt, ... ) {
    if ( !( verbosity & verbosityMask ) ) return;

    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

void vWarning( const int verbosity, const char *fmt, ... ) {
    if ( !( verbosity & verbosityMask ) ) return;

    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

void log( const char *fmt, ... ) {
    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

/* TODO(szucs): Once we have our game loop, we'll want this to
   freeze the game loop and probably throw up a dialog box until
   the user acknowledges the error
*/
void error( const char *fmt, ... ) {
    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

/* TODO(szucs): Once we have our game loop, we'll want this to
   abort the game loop and probably throw up a dialog box
*/
void fatalError( const char *fmt, ... ) {
    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

void warning( const char *fmt, ... ) {
    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}
