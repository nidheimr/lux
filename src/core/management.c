#include "lux/core.h"
#include "core.h"
#include "../debug/debug.h"

#include <stdlib.h>

// public header
// ----------------------------------------------------------------

void lx_poll_events()
{
    GUARD(lt_store == NULL, ("failed to poll events, lux has not been initialised"));
    window_poll_events();
}

void lx_swap_buffers()
{
    GUARD(lt_store == NULL, ("failed to swap buffers, lux has not been initialised"));
    window_swap_buffers();
}

double lx_get_fps()
{
    GUARD(lt_store == NULL, ("failed to get fps, lux has not been initialised"), 0);
    return window_get_fps();
}

double lx_get_delta()
{
    GUARD(lt_store == NULL, ("failed to get delta time, lux has not been initialised"), 0);
    return window_get_delta();
}

double lx_get_time()
{
    GUARD(lt_store == NULL, ("failed to get time elapsed, lux has not been initialised"), 0);
    return window_get_time();
}

int lx_get_width()
{
    GUARD(lt_store == NULL, ("failed to get width, lux has not been initialised"), 0);
    return lt_props.width;
}

int lx_get_height()
{
    GUARD(lt_store == NULL, ("failed to get height, lux has not been initialised"), 0);
    return lt_props.height;
}
