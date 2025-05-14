#pragma once

#define PARAM_GUARD(condition, error, ...)    \
    if (condition)                      \
    {                                   \
        lx_set_last_error error;        \
        return __VA_ARGS__;             \
    }
        
