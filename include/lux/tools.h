#pragma once

//
//  logging
//

void lx_enable_debug_messages(int enabled);
void lx_debug(const char *fmt, ...);

void lx_print(const char* fmt, ...);
void lx_error(const char *fmt, ...);