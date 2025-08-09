#include "input.h"
#include "lux/input.h"

// private source
// ---------------------------------------------------------------- 

static lx_keystate key_tracker[LX_KEY_COUNT] = { LX_RELEASED };

// private header
// ---------------------------------------------------------------- 

void change_key_state(lx_keycode key, lx_keystate state)
{
    if (key < 0 || key >= LX_KEY_COUNT)
        return;

    if (key_tracker[key] != LX_RELEASED && state == LX_PRESSED)
        return;

    key_tracker[key] = state;
}

lx_keystate get_key_state(lx_keycode key)
{
    if (key < 0 || key >= LX_KEY_COUNT)
        return LX_RELEASED;

    lx_keystate origin = key_tracker[key];
    if (origin == LX_PRESSED)
        key_tracker[key] = LX_REPEATED;

    return origin;
}
