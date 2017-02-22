/* HavenLib */

#include <stdarg.h>
#include <stdio.h>

/* TODO(szucs): Remove this and OutputDebugStringA when we
   have a console to print debug messages to
*/
#include <windows.h>

#include "../havenlib/lib.h"

int HavenLib::verbosityMask = VERBOSITY_SYS | VERBOSITY_LIB;

void HavenLib::VPrintf( const int verbosity, const char *fmt, ... ) {
    if ( !( verbosity & verbosityMask ) ) return; 

    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

void HavenLib::VWarning( const int verbosity, const char *fmt, ... ) {
    if ( !( verbosity & verbosityMask ) ) return; 

    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

void HavenLib::Printf( const char *fmt, ... ) {
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
void HavenLib::Error( const char *fmt, ... ) {
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
void HavenLib::FatalError( const char *fmt, ... ) {
    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

void HavenLib::Warning( const char *fmt, ... ) {
    char buf[PRINT_BUF_SIZE];
    va_list args;

    va_start( args, fmt );
    vsnprintf( buf, PRINT_BUF_SIZE, fmt, args );
    va_end( args );

    OutputDebugStringA(buf);
}

int HavenLib::Init() {
    DebugPrintf( VERBOSITY_LIB, "Initialized HavenLib\n");

    return 0;
}

int HavenLib::Deinit() {
    // Nothing to Deinit right now
    return 0;
}
