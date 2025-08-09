#include "input.h"

#include <windows.h> 

#define HIGHEST_KEY_NUMERICAL_VALUE 256 

// private source
// ---------------------------------------------------------------- 

static lx_keycode translation_table[HIGHEST_KEY_NUMERICAL_VALUE] =
{
    // functions
    [VK_ESCAPE] = LX_KEY_ESC,
    [VK_F1] = LX_KEY_F1,
    [VK_F2] = LX_KEY_F2,
    [VK_F3] = LX_KEY_F3,
    [VK_F4] = LX_KEY_F4,
    [VK_F5] = LX_KEY_F5,
    [VK_F6] = LX_KEY_F6,
    [VK_F7] = LX_KEY_F7,
    [VK_F8] = LX_KEY_F8,
    [VK_F9] = LX_KEY_F9,
    [VK_F10] = LX_KEY_F10,
    [VK_F11] = LX_KEY_F11,
    [VK_F12] = LX_KEY_F12,
    [VK_PAUSE] = LX_KEY_PAUSE,
    [VK_SCROLL] = LX_KEY_SCROLLLOCK,
    [VK_NUMLOCK] = LX_KEY_NUMLOCK,

    // numbers (ASCII codes for digits)
    ['1'] = LX_KEY_1,
    ['2'] = LX_KEY_2,
    ['3'] = LX_KEY_3,
    ['4'] = LX_KEY_4,
    ['5'] = LX_KEY_5,
    ['6'] = LX_KEY_6,
    ['7'] = LX_KEY_7,
    ['8'] = LX_KEY_8,
    ['9'] = LX_KEY_9,
    ['0'] = LX_KEY_0,

    // letters (ASCII uppercase)
    ['Q'] = LX_KEY_Q,
    ['W'] = LX_KEY_W,
    ['E'] = LX_KEY_E,
    ['R'] = LX_KEY_R,
    ['T'] = LX_KEY_T,
    ['Y'] = LX_KEY_Y,
    ['U'] = LX_KEY_U,
    ['I'] = LX_KEY_I,
    ['O'] = LX_KEY_O,
    ['P'] = LX_KEY_P,
    ['A'] = LX_KEY_A,
    ['S'] = LX_KEY_S,
    ['D'] = LX_KEY_D,
    ['F'] = LX_KEY_F,
    ['G'] = LX_KEY_G,
    ['H'] = LX_KEY_H,
    ['J'] = LX_KEY_J,
    ['K'] = LX_KEY_K,
    ['L'] = LX_KEY_L,
    ['Z'] = LX_KEY_Z,
    ['X'] = LX_KEY_X,
    ['C'] = LX_KEY_C,
    ['V'] = LX_KEY_V,
    ['B'] = LX_KEY_B,
    ['N'] = LX_KEY_N,
    ['M'] = LX_KEY_M,

    // punctuation
    [VK_OEM_MINUS] = LX_KEY_MINUS,
    [VK_OEM_PLUS] = LX_KEY_EQUAL,
    [VK_OEM_4] = LX_KEY_LEFTBRACE,
    [VK_OEM_6] = LX_KEY_RIGHTBRACE,
    [VK_OEM_1] = LX_KEY_SEMICOLON,
    [VK_OEM_7] = LX_KEY_APOSTROPHE,
    [VK_OEM_3] = LX_KEY_GRAVE,
    [VK_OEM_5] = LX_KEY_BACKSLASH,
    [VK_OEM_COMMA] = LX_KEY_COMMA,
    [VK_OEM_PERIOD] = LX_KEY_DOT,
    [VK_OEM_2] = LX_KEY_SLASH,

    // modifiers
    [VK_LSHIFT] = LX_KEY_LEFTSHIFT,
    [VK_RSHIFT] = LX_KEY_RIGHTSHIFT,
    [VK_LCONTROL] = LX_KEY_LEFTCTRL,
    [VK_RCONTROL] = LX_KEY_RIGHTCTRL,
    [VK_LMENU] = LX_KEY_LEFTALT,
    [VK_RMENU] = LX_KEY_RIGHTALT,
    [VK_CAPITAL] = LX_KEY_CAPSLOCK,

    // whitespace
    [VK_TAB] = LX_KEY_TAB,
    [VK_RETURN] = LX_KEY_ENTER,
    [VK_BACK] = LX_KEY_BACKSPACE,
    [VK_SPACE] = LX_KEY_SPACE,

    // navigation
    [VK_INSERT] = LX_KEY_INSERT,
    [VK_DELETE] = LX_KEY_DELETE,
    [VK_HOME] = LX_KEY_HOME,
    [VK_END] = LX_KEY_END,
    [VK_PRIOR] = LX_KEY_PAGEUP,
    [VK_NEXT] = LX_KEY_PAGEDOWN,
    [VK_UP] = LX_KEY_UP,
    [VK_DOWN] = LX_KEY_DOWN,
    [VK_LEFT] = LX_KEY_LEFT,
    [VK_RIGHT] = LX_KEY_RIGHT,

    // numpad
    [VK_NUMPAD0] = LX_KEY_KP0,
    [VK_NUMPAD1] = LX_KEY_KP1,
    [VK_NUMPAD2] = LX_KEY_KP2,
    [VK_NUMPAD3] = LX_KEY_KP3,
    [VK_NUMPAD4] = LX_KEY_KP4,
    [VK_NUMPAD5] = LX_KEY_KP5,
    [VK_NUMPAD6] = LX_KEY_KP6,
    [VK_NUMPAD7] = LX_KEY_KP7,
    [VK_NUMPAD8] = LX_KEY_KP8,
    [VK_NUMPAD9] = LX_KEY_KP9,
    [VK_DECIMAL] = LX_KEY_KPDOT,
    [VK_ADD] = LX_KEY_KPPLUS,
    [VK_SUBTRACT] = LX_KEY_KPMINUS,
    [VK_MULTIPLY] = LX_KEY_KPASTERISK,
    [VK_DIVIDE] = LX_KEY_KPSLASH,
};


// private header
// ---------------------------------------------------------------- 

lx_keycode code_to_key(int code)
{
    if (code < 0 || code >= HIGHEST_KEY_NUMERICAL_VALUE)
        return LX_KEY_UNKNOWN;

    return translation_table[code];
}
