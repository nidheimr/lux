#include "lux/debug.h"
#include "../core/core.h"

#include <stdarg.h>
#include <stdio.h>

// public header 
// ---------------------------------------------------------------- 

void lx_error(const char* fmt, ...)
{
    if (fmt == NULL || lt_props.on_error == NULL)
        return;

    va_list args;
    va_start(args, fmt);

    char desc[512];
    vsnprintf(desc, sizeof(desc), fmt, args);

    va_end(args);

    lt_props.on_error(desc);
}
