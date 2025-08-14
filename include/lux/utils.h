#pragma once

#include "api.h"
LX_BEGIN_HEADER

// file
// ---------------------------------------------------------------- 

/**
 * @brief Reads a file as a c-string. The entire file is read in one go,
 * therefore this may be slow with larger files.
 *
 * It is the responsibility of the user to free the c-string when they are
 * done with it.
 *
 * @param file The file to read.
 *
 * @return The c-string representation of the file or NULL on failure.
 */
LX_API char* lx_read_file(const char* file);

LX_END_HEADER
