/* State and interface for all that good system stuff */

#ifndef __SYS_LOCAL__
#define __SYS_LOCAL__

#include "console.h"
#include "debug.h"

typedef struct {
    const char *title;
    int screenWidth;
    int screenHeight;
} SysVars_t;

extern SysVars_t Sys;

#endif /* __SYS_LOCAL__ */
