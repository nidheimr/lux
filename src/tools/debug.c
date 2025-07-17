#include "lux/tools.h"

#include "debug.h"

#include <stdarg.h>
#include <stdio.h>

//
//  private
//

static lx_error_callback bound_errcb = NULL;
static lx_debug_callback bound_dbgcb = NULL;

void set_err_cb(lx_error_callback errcb)
{
    bound_errcb = errcb;
}

void set_dbg_cb(lx_debug_callback dbgcb)
{
    bound_dbgcb = dbgcb;
}

void produce_error(const char* fmt, ...)
{
    if (bound_errcb == NULL)
        return;

    va_list args;
    va_start(args, fmt);

    char err[512];
    vsnprintf(err, 512, fmt, args);

    va_end(args);
    bound_errcb(err);
}

void produce_debug(const char* fmt, ...)
{
    if (bound_dbgcb == NULL)
        return;

    va_list args;
    va_start(args, fmt);

    char dbg[512];
    vsnprintf(dbg, 512, fmt, args);

    va_end(args);
    bound_dbgcb(dbg);
}
