#pragma once

#include <stddef.h>

//
//  debug 
//

/**
 * @brief Sets whether the debug messages should be printed or not. Errors and regular
 * prints are not affected by this.
 *
 * @param enabled 1 for enabled, 0 for disabled.
 */
void lx_enable_debug_messages(int enabled);

/**
 * @brief Sets the last error produced and stores it for retrieval by
 * `lx_get_last_error`.
 *
 * @param fmt The printf-style format string.
 * @param ... Any formatting arguements.
 */
void lx_set_last_error(const char* fmt, ...);

/**
 * @brief Gets the last error produced, stored by `lx_set_last_error`, and places it
 * into `buffer`.
 *
 * @param buffer The buffer which will hold the last error.
 * @param buffer_size The size of said buffer.
 */
void lx_get_last_error(char* buffer, size_t buffer_size);

/**
 * @brief Prints to the standard output with a debug prefix. These messages can be
 * toggled using `lx_enable_debug_messages`.
 *
 * @param fmt The printf-style format string.
 * @param ... Any formatting arguements.
 */
void lx_debug(const char *fmt, ...);

/**
 * @brief Prints to the standard output with a print prefix.
 *
 * @param fmt The printf-style format string.
 * @param ... Any formatting arguements.
 */
void lx_print(const char* fmt, ...);

/**
 * @brief Prints to the standard output with an error prefix.
 *
 * @param fmt The printf-style format string.
 * @param ... Any formatting arguements.
 */
void lx_error(const char *fmt, ...);

/**
 * @brief Prints to the standard output the last error produced. Works identically to
 * using `lx_get_last_error` with `lx_error`.   
 */
void lx_print_last_error();

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
