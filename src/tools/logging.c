#include "lux/tools.h"

#include <stdarg.h>
#include <stdio.h>

//
//	private
//

int debug_messages_enabled = 0;

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