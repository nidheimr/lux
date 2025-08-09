#pragma once

#include "api.h"
LX_BEGIN_HEADER

// types
// -----------------------------------------------------------------

typedef enum _lx_keystate
{
    LX_RELEASED,
    LX_PRESSED,
    LX_REPEATED
}
lx_keystate;

typedef enum _lx_keycode
{
    LX_KEY_UNKNOWN = 0,

    // functions
    LX_KEY_ESC,
    LX_KEY_F1,
    LX_KEY_F2,
    LX_KEY_F3,
    LX_KEY_F4,
    LX_KEY_F5,
    LX_KEY_F6,
    LX_KEY_F7,
    LX_KEY_F8,
    LX_KEY_F9,
    LX_KEY_F10,
    LX_KEY_F11,
    LX_KEY_F12,
    LX_KEY_PAUSE,
    LX_KEY_SCROLLLOCK,
    LX_KEY_NUMLOCK,

    // numbers
    LX_KEY_1,
    LX_KEY_2,
    LX_KEY_3,
    LX_KEY_4,
    LX_KEY_5,
    LX_KEY_6,
    LX_KEY_7,
    LX_KEY_8,
    LX_KEY_9,
    LX_KEY_0,

    // letters
    LX_KEY_Q,
    LX_KEY_W,
    LX_KEY_E,
    LX_KEY_R,
    LX_KEY_T,
    LX_KEY_Y,
    LX_KEY_U,
    LX_KEY_I,
    LX_KEY_O,
    LX_KEY_P,
    LX_KEY_A,
    LX_KEY_S,
    LX_KEY_D,
    LX_KEY_F,
    LX_KEY_G,
    LX_KEY_H,
    LX_KEY_J,
    LX_KEY_K,
    LX_KEY_L,
    LX_KEY_Z,
    LX_KEY_X,
    LX_KEY_C,
    LX_KEY_V,
    LX_KEY_B,
    LX_KEY_N,
    LX_KEY_M,

    // punctuation
    LX_KEY_MINUS,
    LX_KEY_EQUAL,
    LX_KEY_LEFTBRACE,
    LX_KEY_RIGHTBRACE,
    LX_KEY_SEMICOLON,
    LX_KEY_APOSTROPHE,
    LX_KEY_GRAVE,
    LX_KEY_BACKSLASH,
    LX_KEY_COMMA,
    LX_KEY_DOT,
    LX_KEY_SLASH,

    // modifiers
    LX_KEY_LEFTSHIFT,
    LX_KEY_RIGHTSHIFT,
    LX_KEY_LEFTCTRL,
    LX_KEY_RIGHTCTRL,
    LX_KEY_LEFTALT,
    LX_KEY_RIGHTALT,
    LX_KEY_CAPSLOCK,

    // whitespace
    LX_KEY_TAB,
    LX_KEY_ENTER,
    LX_KEY_BACKSPACE,
    LX_KEY_SPACE,

    // navigation
    LX_KEY_INSERT,
    LX_KEY_DELETE,
    LX_KEY_HOME,
    LX_KEY_END,
    LX_KEY_PAGEUP,
    LX_KEY_PAGEDOWN,
    LX_KEY_UP,
    LX_KEY_DOWN,
    LX_KEY_LEFT,
    LX_KEY_RIGHT,

    // numpad
    LX_KEY_KP0,
    LX_KEY_KP1,
    LX_KEY_KP2,
    LX_KEY_KP3,
    LX_KEY_KP4,
    LX_KEY_KP5,
    LX_KEY_KP6,
    LX_KEY_KP7,
    LX_KEY_KP8,
    LX_KEY_KP9,
    LX_KEY_KPDOT,
    LX_KEY_KPPLUS,
    LX_KEY_KPMINUS,
    LX_KEY_KPASTERISK,
    LX_KEY_KPSLASH,
    LX_KEY_KPENTER,

    LX_KEY_COUNT
}
lx_keycode;

// query 
// -----------------------------------------------------------------

/**
 * @brief Returns the state of the given key.
 *
 * If the key is not pressed, then `LX_RELEASED` is returned.
 *
 * If the key is pressed then `LX_PRESSED` is returned.
 *
 * If the key is pressed and has already been queried then `LX_REPEATED` is
 * returned.
 *
 * @param key The key to query.
 *
 * @return An enum representing the state of the key.
 */
lx_keystate lx_get_key_state(lx_keycode key);

LX_END_HEADER
