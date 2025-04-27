#pragma once

//
//  debug 
//

void lx_enable_debug_messages(int enabled);
void lx_set_last_error(const char* fmt, ...);
void lx_get_last_error(char* buffer, size_t buffer_size);

void lx_debug(const char *fmt, ...);
void lx_print(const char* fmt, ...);
void lx_error(const char *fmt, ...);
void lx_print_last_error();

//
//  file io
//

const char* lx_read_file(const char* file);
