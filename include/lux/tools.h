#pragma once

#include "external.h"
LX_BEGIN_HEADER

#include <stddef.h>

//
//  debug
//

typedef void (*lx_error_callback)(const char* error);
typedef void (*lx_debug_callback)(const char* debug);

/**
 * @brief Sets the given function to the be the callback function for all
 * future produced error messages.
 *
 * @param callback the callback function.
 */
void lx_set_error_callback(lx_error_callback callback);

/**
 * @brief Sets the given function to the be the callback function for all
 * future produced debug messages.
 *
 * @param callback the callback function.
 */
void lx_set_debug_callback(lx_debug_callback callback);

/**
 * @brief Sends an error message to the currently bound error callback.
 *
 * @param fmt The printf-style format string.
 * @param ... Any formatting arguements.
 */
void lx_produce_error(const char* fmt, ...);

/**
 * @brief Sends a debug message to the currently bound debug callback.
 *
 * @param fmt The printf-style format string.
 * @param ... Any formatting arguements.
 */
void lx_produce_debug(const char* fmt, ...);

//
//  file io
//

/**
 * @brief Reads a file as a string of characters into a buffer then returns a pointer
 * to the caller. This buffer **must be freed** by the caller after use.
 *
 * @param file The file to read.
 *
 * @return A pointer to the char* buffer or NULL if failed.
 */
const char* lx_read_file(const char* file);

LX_END_HEADER
