#include "input.h"
#include "lux/input.h"
#include "../core/core.h"

#include <stddef.h>

// private header
// ---------------------------------------------------------------- 

void change_key_state(lx_keycode key, lx_keystate state)
{
    if (key < 0 || key >= LX_KEY_COUNT)
        return;

    if (lt_store->key_tracker[key] != LX_RELEASED && state == LX_PRESSED)
        return;

    lt_store->key_tracker[key] = state;
}

lx_keystate get_key_state(lx_keycode key)
{
    if (key < 0 || key >= LX_KEY_COUNT)
        return LX_RELEASED;

    lx_keystate origin = lt_store->key_tracker[key];
    if (origin == LX_PRESSED)
        lt_store->key_tracker[key] = LX_REPEATED;

    return origin;
}

void update_mouse_position(double x, double y)
{
    if (x < 0 || x >= lt_props.width)
        return;

    if (y < 0 || y >= lt_props.height)
        return;

    lt_store->mouse_tracker.x = x;
    lt_store->mouse_tracker.y = y;
}

lx_mousepos get_mouse_position()
{
    return lt_store->mouse_tracker;
}

void update_mouse_scroll(double scroll)
{
    lt_store->scroll_amount += scroll;
}

void reset_mouse_scroll()
{
    lt_store->scroll_amount = 0;
}

double get_mouse_scroll()
{
    return lt_store->scroll_amount;
}
