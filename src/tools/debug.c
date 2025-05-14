#include "lux/tools.h"

#include "debug.h"

#include <stdarg.h>
#include <stdio.h>

//
//	private
//

static int debug_messages_enabled = 0;
static char last_error[512] = { 0 };

#define UNWRAP_THEN_STDPRINT(prefix)	\
	va_list args;						\
	va_start(args, fmt);				\
	stdprint(prefix, fmt, args);		\
	va_end(args)


static void stdprint(const char *prefix, const char *fmt, va_list args)
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
    PARAM_GUARD(enabled > 1 || enabled < 0, ("could not toggle debug messages, expected 1 (enabled) or 0 (disabled) but got %d", enabled));
	debug_messages_enabled = enabled;
}

void lx_set_last_error(const char* fmt, ...)
{
    PARAM_GUARD(fmt == NULL, ("could not set last error to null"));

    va_list args;
    va_start(args, fmt);

    vsnprintf(last_error, sizeof(last_error), fmt, args);

    va_end(args);
}

void lx_get_last_error(char* buffer, size_t buffer_size)
{
    PARAM_GUARD(buffer == NULL, ("could not place last error into null buffer"));
    PARAM_GUARD(buffer_size < 1 || buffer_size > 512, ("could not place last error into improperly sized buffer, expected size of 1-512 but got %d", buffer_size));

    snprintf(buffer, buffer_size, "%s", last_error);
}

void lx_debug(const char *fmt, ...)
{
	if (!debug_messages_enabled)
		return;

    PARAM_GUARD(fmt == NULL, ("could not debug null message"));
	UNWRAP_THEN_STDPRINT("\033[34mDEBUG \033[38;2;80;80;80m>> \033[0m");
}

void lx_print(const char* fmt, ...)
{
    PARAM_GUARD(fmt == NULL, ("could not print null message"));
	UNWRAP_THEN_STDPRINT("\033[32mPRINT \033[38;2;80;80;80m>> \033[0m");
}

void lx_error(const char *fmt, ...)
{
    PARAM_GUARD(fmt == NULL, ("could not error null message"));
	UNWRAP_THEN_STDPRINT("\033[31mERROR \033[38;2;80;80;80m>> \033[0m");
}

void lx_print_last_error()
{
    lx_error("%s", last_error);
}
