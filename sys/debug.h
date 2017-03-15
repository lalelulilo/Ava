
/* Debug Functions */

#ifndef __SYS_DEBUG_H__
#define __SYS_DEBUG_H__

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
#define LOG( verbosity, fmt, ... ) \
    do { vLog(verbosity, "%s(%d): " fmt,                      \
              __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define LOG_IF( cond, verbosity, fmt, ... )                 \
    do { if (cond) vLog(verbosity, "%s(%d): " fmt,  \
                        __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

// Error occured, like model failed to load, but we can continue the game
#define AVA_ERROR( fmt, ... ) \
    do { error("%s(%d): " fmt, \
               __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define AVA_ERROR_IF( cond, fmt, ... ) \
    do { if (cond) error("%s(%d): " fmt, \
                         __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

// Fatal error occured which means we can't continue the game i.e. failed to init important component 
#define FATAL_ERROR( fmt, ... )                                          \
    do { fatalError("%s(%d): " fmt,                     \
                    __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define FATAL_ERROR_IF( cond, fmt, ... )                                  \
    do { if (cond) fatalError("%s(%d): " fmt,             \
                              __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

// Somewhere in-between a Log and an Error, you'll have to use your best judgement :)
#define WARNING( verbosity, fmt, ... ) \
    do { vWarning(verbosity, "%s(%d): " fmt, \
                  __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)
#define WARNING_IF( cond, verbosity, fmt, ... )                  \
    do { if (cond) VWarning(verbosity, "%s(%d): " fmt, \
                            __FUNCTION__, __LINE__, __VA_ARGS__); } while (0)

/* Debug functions for printing */
void vLog( const int verbosity, const char *fmt, ... );
void vWarning( const int verbosity, const char *fmt, ... );
void log( const char *fmt, ... );
void warning( const char *fmt, ... );
NO_RETURN void error( const char *fmt, ... );
NO_RETURN void fatalError( const char *fmt, ... );

#endif /* !__SYS_DEBUG_H__ */
