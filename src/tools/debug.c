#include "lux/tools.h"

#include <stdarg.h>
#include <stdio.h>

//
//	private
//

int debug_messages_enabled = 0;
char last_error[512] = { 0 };

#define UNWRAP_THEN_STDPRINT(prefix)	\
	va_list args;						\
	va_start(args, fmt);				\
	stdprint(prefix, fmt, args);		\
	va_end(args)


void stdprint(const char *prefix, const char *fmt, va_list args)
{
	printf("%s", prefix);
	vprintf(fmt, args);
	printf("\n");
}

//
//	public
//

void lx_enable_debug_messages(int enabled)
{
	debug_messages_enabled = enabled;
}

void lx_set_last_error(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    vsnprintf(last_error, sizeof(last_error), fmt, args);

    va_end(args);
}

void lx_get_last_error(char* buffer, size_t buffer_size)
{
    snprintf(buffer, buffer_size, "%s", last_error);
}

void lx_debug(const char *fmt, ...)
{
	if (!debug_messages_enabled)
		return;

	UNWRAP_THEN_STDPRINT("\033[34mDEBUG \033[38;2;80;80;80m>> \033[0m");
}

void lx_print(const char* fmt, ...)
{
	UNWRAP_THEN_STDPRINT("\033[32mPRINT \033[38;2;80;80;80m>> \033[0m");
}

void lx_error(const char *fmt, ...)
{
	UNWRAP_THEN_STDPRINT("\033[31mERROR \033[38;2;80;80;80m>> \033[0m");
}

void lx_print_last_error()
{
    lx_error("%s", last_error);
}
