#pragma once

#include "lux/output.h"

#define PARAM_GUARD(condition, error, ...)      \
    if (condition)                              \
    {                                           \
        produce_error error;                 \
        return __VA_ARGS__;                     \
    }

void set_err_cb(lx_error_callback errcb);
void set_dbg_cb(lx_debug_callback dbgcb);

void produce_error(const char* fmt, ...);
void produce_debug(const char* fmt, ...);
