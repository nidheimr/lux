#include "lux/input.h"
#include "input.h"
#include "../debug/debug.h"
#include "../core/core.h"

#include <stddef.h>

// public header
// ----------------------------------------------------------------

lx_keystate lx_get_key_state(lx_keycode key)
{
    GUARD(lt_store == NULL, ("failed to get key state, lux has not been initialised"), LX_RELEASED);
    GUARD(key < 0 || key >= LX_KEY_COUNT, ("could not query invalid key"), LX_RELEASED);
    return get_key_state(key);
}

lx_mousepos lx_get_mouse_pos()
{
    GUARD(lt_store == NULL, ("failed to get mouse position, lux has not been initialised"), (lx_mousepos){ 0.0 });
    return get_mouse_position();
}

double lx_get_mouse_scroll()
{
    GUARD(lt_store == NULL, ("failed to get mouse scroll, lux has not been initialised"), 0.0);
    return get_mouse_scroll();
}
