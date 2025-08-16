#pragma once

#include "api.h"
LX_BEGIN_HEADER

// emission
// ---------------------------------------------------------------- 

/**
 * @brief Sends an error to the bound error callback. This allows for uniform
 * error handling.
 *
 * The error callback is set during initialisation, if set to NULL then all
 * calls to this function are ignored.
 *
 * Absolutely do not call this function in the error callback itself, you will
 * create endless recursion. No good can come of that.
 *
 * @param fmt The printf-style format string.
 * @param ... The arguments to the format string.
 */
LX_API void lx_error(const char* fmt, ...);

LX_END_HEADER
