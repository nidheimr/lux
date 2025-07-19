#pragma once

// macros
// ---------------------------------------------------------------- 

#define GUARD(cond, err, ...)                                   \
    if (cond)                                                   \
    {                                                           \
        emit_error err;                                         \
        return __VA_ARGS__;                                     \
    }                                                           \

// emission 
// ----------------------------------------------------------------

// send a debug message to the bound callback
void emit_error(const char* fmt, ...);
