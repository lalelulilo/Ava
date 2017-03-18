
/* HavenLib */
/* TODO(szucs): Add HavenLib error codes somewhere */

#ifndef __HAVENLIB_H__
#define __HAVENLIB_H__

#include "precompiled.h"

/* Specifies that a function will never return, and that
   any conditions which lead to them being called are guaranteed
   to be false

   This prevents spurious warnings, and helps the optimizer

   NOTE(szucs): If we use this elsewhere, we should push it into '../havenlib/sys/sys_define.h'
*/
#define NO_RETURN  __declspec(noreturn)

#define PRINT_BUF_SIZE     1024   // max length of our debug strings

// Verbosity masks will allow you to disable what is and isn't printed
#define VERBOSITY_LIB    ( 0x01 )    // HavenLib
#define VERBOSITY_SYS    ( 0x02 )    // System related

/* Convenience macros for debugging and errors. These will add the file name, function name,
   and line number to the debug message. These will be optimized out if DEBUG == 0

   Do while loop allows you to treat it like a normal function
*/
// Inform us that something happened, like when HavenLib is initialized
#define DebugPrintf( verbosity, fmt, ... ) \
    do { if (DEBUG) HavenLib::VPrintf(verbosity, "%s(%d): " fmt, \
                                      __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define DebugPrintfIf( cond, verbosity, fmt, ... )                 \
    do { if (DEBUG && cond) HavenLib::VPrintf(verbosity, "%s(%d): " fmt,  \
                                      __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

// Error occured, like model failed to load, but we can continue the game
#define DebugError( fmt, ... ) \
    do { if (DEBUG) HavenLib::Error("%s(%d): " fmt, \
                                              __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define DebugErrorIf( cond, fmt, ... ) \
    do { if (DEBUG && cond) HavenLib::Error("%s(%d): " fmt, \
                                             __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

// Fatal error occured which means we can't continue the game i.e. failed to init HavenLib
#define DebugFatalError( fmt, ... )                                          \
    do { if (DEBUG) HavenLib::FatalError("%s(%d): " fmt,                     \
                                    __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define DebugFatalErrorIf( cond, fmt, ... )                                  \
    do { if (DEBUG && cond) HavenLib::FatalError("%s(%d): " fmt,             \
                                            __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

// Somewhere in-between a Printf and an Error, you'll have to use your best judgement :)
#define DebugWarning( verbosity, fmt, ... ) \
    do { if (DEBUG) HavenLib::VWarning(verbosity, "%s(%d): " fmt, \
                                                  __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define DebugWarningIf( cond, verbosity, fmt, ... )                \
    do { if (DEBUG && cond) HavenLib::VWarning(verbosity, "%s(%d): " fmt, \
                                       __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

class HavenLib {
public:
    /* The verbosityMask decides what will actually be printed to console, and what won't.
       This is a bitmask, so for example you can turn off HavenLib debugging by clearing
       VERBOSITY_LIB
    */
    static int verbosityMask;

    /* Start-up and teardown for HavenLib */
    static int Init();
    static int Deinit();

    /* Debug functions for printing */
    /* TODO(szucs): ALL of these functions can be moved from printing to stdout/stderr and into
       an in-game console at some point. Likely we'd like to do this by queuing all the messages up
       for a separate debug thread, which won't exist on release build, which will flush to the
       console every second

       If you peek at the DOOM3 code, you'll see it just constructs a string then passes it onto
       common->Printf, which then seems to be defined in the actual game. It may be smarter to do
       that, as this is a library for basic functionality and NOT the game engine

       Right now though, we can just use these functions and changing it later won't break anything
    */
    static void VPrintf( const int verbosity, const char *fmt, ... );
    static void VWarning( const int verbosity, const char *fmt, ... );
    static void Printf( const char *fmt, ... );
    static void Warning( const char *fmt, ... );
    NO_RETURN static void Error( const char *fmt, ... );
    NO_RETURN static void FatalError( const char *fmt, ... );
};

#endif /* !__HAVENLIB_H__ */