#pragma once

//
//  logging
//

void lx_enable_debug_messages(int enabled);
void lx_debug(const char *fmt, ...);

void lx_print(const char* fmt, ...);
void lx_error(const char *fmt, ...);

//
//  io
//

char* lx_read_file_as_str(const char* file_path);