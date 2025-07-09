#include "lux/tools.h"

#include "debug.h"

#include <stdarg.h>
#include <stdio.h>

//
//	private
//

static void standard_error_callback(const char* error)
{
    printf("%s %s\n", "\033[31mERROR \033[38;2;80;80;80m>> \033[0m", error);
}

static void standard_debug_callback(const char* debug)
{
    printf("%s %s\n", "\033[34mDEBUG \033[38;2;80;80;80m>> \033[0m", debug);
}

static lx_error_callback errcb = standard_error_callback;
static lx_debug_callback dbgcb = standard_debug_callback;

//
//	public
//

void lx_set_error_callback(lx_error_callback callback)
{
    errcb = callback; 
}

void lx_set_debug_callback(lx_debug_callback callback)
{
    dbgcb = callback; 
}

void lx_produce_error(const char* fmt, ...)
{
    PARAM_GUARD(fmt == NULL, ("could not produce null error"));

    if (errcb == NULL)
        return;

    va_list args;
    va_start(args, fmt);

    char err[512];
    vsnprintf(err, 512, fmt, args);

    va_end(args);
    errcb(err);
}

void lx_produce_debug(const char* fmt, ...)
{
    PARAM_GUARD(fmt == NULL, ("could not produce null debug"));

    if (dbgcb == NULL)
        return;

    va_list args;
    va_start(args, fmt);

    char dbg[512];
    vsnprintf(dbg, 512, fmt, args);

    va_end(args);
    dbgcb(dbg);
}
