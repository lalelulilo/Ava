
/* Debug Functions */

#ifndef __DEBUG_H__
#define __DEBUG_H__

/* Specifies that a function will never return, and that
   any conditions which lead to them being called are guaranteed
   to be false

   This prevents spurious warnings, and helps the optimizer
*/
#define NO_RETURN  __declspec(noreturn)

#define PRINT_BUF_SIZE     1024      // max length of our debug strings

// Verbosity masks will allow you to disable what is and isn't printed
#define VERBOSITY_SYS    ( 0x01 )    // System related

/* Convenience macros for debugging and errors. These will add the file name, function name,
   and line number to the debug message. These will be optimized out if DEBUG == 0

   Do while loop allows you to treat it like a normal function
*/
// Inform us that something happened, like when the game is initialized
#define debugPrintf( verbosity, fmt, ... ) \
    do { if (DEBUG) printf(verbosity, "%s(%d): " fmt, \
                           __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define debugPrintfIf( cond, verbosity, fmt, ... )                 \
    do { if (DEBUG && cond) vPrintf(verbosity, "%s(%d): " fmt,  \
                                    __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

// Error occured, like model failed to load, but we can continue the game
#define debugError( fmt, ... ) \
    do { if (DEBUG) error("%s(%d): " fmt, \
                          __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define debugErrorIf( cond, fmt, ... ) \
    do { if (DEBUG && cond) error("%s(%d): " fmt, \
                                  __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

// Fatal error occured which means we can't continue the game i.e. failed to init important component 
#define debugFatalError( fmt, ... )                                          \
    do { if (DEBUG) fatalError("%s(%d): " fmt,                     \
                               __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define debugFatalErrorIf( cond, fmt, ... )                                  \
    do { if (DEBUG && cond) fatalError("%s(%d): " fmt,             \
                                       __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

// Somewhere in-between a Printf and an Error, you'll have to use your best judgement :)
#define debugWarning( verbosity, fmt, ... ) \
    do { if (DEBUG) vWarning(verbosity, "%s(%d): " fmt, \
                                         __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define debugWarningIf( cond, verbosity, fmt, ... )                \
    do { if (DEBUG && cond) VWarning(verbosity, "%s(%d): " fmt, \
                                     __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

/* Debug functions for printing */
void vPrintf( const int verbosity, const char *fmt, ... );
void vWarning( const int verbosity, const char *fmt, ... );
void printf( const char *fmt, ... );
void warning( const char *fmt, ... );
NO_RETURN void error( const char *fmt, ... );
NO_RETURN void fatalError( const char *fmt, ... );

#endif /* !__DEBUG_H__ */
