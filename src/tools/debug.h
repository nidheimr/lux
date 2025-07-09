#pragma once

#define PARAM_GUARD(condition, error, ...)      \
    if (condition)                              \
    {                                           \
        lx_produce_error error;                 \
        return __VA_ARGS__;                     \
    }
        
