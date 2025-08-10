#include "input.h"
#include "lux/input.h"

#include <linux/input-event-codes.h>

#define HIGHEST_KEY_NUMERICAL_VALUE 512

// private source
// ---------------------------------------------------------------- 

static lx_keycode translation_table[HIGHEST_KEY_NUMERICAL_VALUE] =
{
    // functions
    [KEY_ESC] = LX_KEY_ESC,
    [KEY_F1] = LX_KEY_F1,
    [KEY_F2] = LX_KEY_F2,
    [KEY_F3] = LX_KEY_F3,
    [KEY_F4] = LX_KEY_F4,
    [KEY_F5] = LX_KEY_F5,
    [KEY_F6] = LX_KEY_F6,
    [KEY_F7] = LX_KEY_F7,
    [KEY_F8] = LX_KEY_F8,
    [KEY_F9] = LX_KEY_F9,
    [KEY_F10] = LX_KEY_F10,
    [KEY_F11] = LX_KEY_F11,
    [KEY_F12] = LX_KEY_F12,
    [KEY_PAUSE] = LX_KEY_PAUSE,
    [KEY_SCROLLLOCK] = LX_KEY_SCROLLLOCK,
    [KEY_NUMLOCK] = LX_KEY_NUMLOCK,

    // numbers
    [KEY_1] = LX_KEY_1,
    [KEY_2] = LX_KEY_2,
    [KEY_3] = LX_KEY_3,
    [KEY_4] = LX_KEY_4,
    [KEY_5] = LX_KEY_5,
    [KEY_6] = LX_KEY_6,
    [KEY_7] = LX_KEY_7,
    [KEY_8] = LX_KEY_8,
    [KEY_9] = LX_KEY_9,
    [KEY_0] = LX_KEY_0,

    // letters
    [KEY_Q] = LX_KEY_Q,
    [KEY_W] = LX_KEY_W,
    [KEY_E] = LX_KEY_E,
    [KEY_R] = LX_KEY_R,
    [KEY_T] = LX_KEY_T,
    [KEY_Y] = LX_KEY_Y,
    [KEY_U] = LX_KEY_U,
    [KEY_I] = LX_KEY_I,
    [KEY_O] = LX_KEY_O,
    [KEY_P] = LX_KEY_P,
    [KEY_A] = LX_KEY_A,
    [KEY_S] = LX_KEY_S,
    [KEY_D] = LX_KEY_D,
    [KEY_F] = LX_KEY_F,
    [KEY_G] = LX_KEY_G,
    [KEY_H] = LX_KEY_H,
    [KEY_J] = LX_KEY_J,
    [KEY_K] = LX_KEY_K,
    [KEY_L] = LX_KEY_L,
    [KEY_Z] = LX_KEY_Z,
    [KEY_X] = LX_KEY_X,
    [KEY_C] = LX_KEY_C,
    [KEY_V] = LX_KEY_V,
    [KEY_B] = LX_KEY_B,
    [KEY_N] = LX_KEY_N,
    [KEY_M] = LX_KEY_M,

    // punctuation
    [KEY_MINUS] = LX_KEY_MINUS,
    [KEY_EQUAL] = LX_KEY_EQUAL,
    [KEY_LEFTBRACE] = LX_KEY_LEFTBRACE,
    [KEY_RIGHTBRACE] = LX_KEY_RIGHTBRACE,
    [KEY_SEMICOLON] = LX_KEY_SEMICOLON,
    [KEY_APOSTROPHE] = LX_KEY_APOSTROPHE,
    [KEY_GRAVE] = LX_KEY_GRAVE,
    [KEY_BACKSLASH] = LX_KEY_BACKSLASH,
    [KEY_COMMA] = LX_KEY_COMMA,
    [KEY_DOT] = LX_KEY_DOT,
    [KEY_SLASH] = LX_KEY_SLASH,

    // modifiers
    [KEY_LEFTSHIFT] = LX_KEY_LEFTSHIFT,
    [KEY_RIGHTSHIFT] = LX_KEY_RIGHTSHIFT,
    [KEY_LEFTCTRL] = LX_KEY_LEFTCTRL,
    [KEY_RIGHTCTRL] = LX_KEY_RIGHTCTRL,
    [KEY_LEFTALT] = LX_KEY_LEFTALT,
    [KEY_RIGHTALT] = LX_KEY_RIGHTALT,
    [KEY_CAPSLOCK] = LX_KEY_CAPSLOCK,

    // whitespace
    [KEY_TAB] = LX_KEY_TAB,
    [KEY_ENTER] = LX_KEY_ENTER,
    [KEY_BACKSPACE] = LX_KEY_BACKSPACE,
    [KEY_SPACE] = LX_KEY_SPACE,

    // navigation
    [KEY_INSERT] = LX_KEY_INSERT,
    [KEY_DELETE] = LX_KEY_DELETE,
    [KEY_HOME] = LX_KEY_HOME,
    [KEY_END] = LX_KEY_END,
    [KEY_PAGEUP] = LX_KEY_PAGEUP,
    [KEY_PAGEDOWN] = LX_KEY_PAGEDOWN,
    [KEY_UP] = LX_KEY_UP,
    [KEY_DOWN] = LX_KEY_DOWN,
    [KEY_LEFT] = LX_KEY_LEFT,
    [KEY_RIGHT] = LX_KEY_RIGHT,

    // numpad
    [KEY_KP0] = LX_KEY_KP0,
    [KEY_KP1] = LX_KEY_KP1,
    [KEY_KP2] = LX_KEY_KP2,
    [KEY_KP3] = LX_KEY_KP3,
    [KEY_KP4] = LX_KEY_KP4,
    [KEY_KP5] = LX_KEY_KP5,
    [KEY_KP6] = LX_KEY_KP6,
    [KEY_KP7] = LX_KEY_KP7,
    [KEY_KP8] = LX_KEY_KP8,
    [KEY_KP9] = LX_KEY_KP9,
    [KEY_KPDOT] = LX_KEY_KPDOT,
    [KEY_KPPLUS] = LX_KEY_KPPLUS,
    [KEY_KPMINUS] = LX_KEY_KPMINUS,
    [KEY_KPASTERISK] = LX_KEY_KPASTERISK,
    [KEY_KPSLASH] = LX_KEY_KPSLASH,
    [KEY_KPENTER] = LX_KEY_ENTER,

    // mouse
    [BTN_LEFT] = LX_MOUSE_LEFT,
    [BTN_RIGHT] = LX_MOUSE_RIGHT,
    [BTN_MIDDLE] = LX_MOUSE_MIDDLE
};

// private header
// ---------------------------------------------------------------- 

lx_keycode code_to_key(int code)
{
    if (code < 0 || code >= HIGHEST_KEY_NUMERICAL_VALUE)
        return LX_KEY_UNKNOWN;

    return translation_table[code];
}
