#include "lux/input.h"
#include "input.h"
#include "../debug/debug.h"

// public header
// ----------------------------------------------------------------

lx_keystate lx_get_key_state(lx_keycode key)
{
    GUARD(key < 0 || key >= LX_KEY_COUNT, ("could not query invalid key"), LX_RELEASED);
    return get_key_state(key);
}
