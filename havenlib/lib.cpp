/* havenLib */

#include <stdarg.h>
#include <stdio.h>

/* TODO(szucs): Remove this and OutputDebugStringA when we
   have a console to print debug messages to
*/
#include <windows.h>

#include "../havenlib/lib.h"

int havenLib::verbosityMask = VERBOSITY_SYS | VERBOSITY_LIB;

void havenLib::VPrintf( const int verbosity, const char *fmt, ... ) {
    if ( !( verbosity & verbosityMask ) ) return; 

    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

void havenLib::VWarning( const int verbosity, const char *fmt, ... ) {
    if ( !( verbosity & verbosityMask ) ) return; 

    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

void havenLib::Printf( const char *fmt, ... ) {
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
void havenLib::Error( const char *fmt, ... ) {
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
void havenLib::FatalError( const char *fmt, ... ) {
    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

void havenLib::Warning( const char *fmt, ... ) {
    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

int havenLib::Init() {
    DebugPrintf( VERBOSITY_LIB, "Initialized havenLib\n");

    return 0;
}

int havenLib::Deinit() {
    // Nothing to Deinit right now
    return 0;
}
