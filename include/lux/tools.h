#pragma once

#include "external.h"
LX_BEGIN_HEADER

//
//  debug
//



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
