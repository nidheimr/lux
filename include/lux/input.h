#pragma once

#include "external.h"
LX_BEGIN_HEADER

//
//  codes
//

typedef enum _lx_kb_key
{
    // letters
    LX_KEY_A,
    LX_KEY_B,
    LX_KEY_C,
    LX_KEY_D,
    LX_KEY_E,
    LX_KEY_F,
    LX_KEY_G,
    LX_KEY_H,
    LX_KEY_I,
    LX_KEY_J,
    LX_KEY_K,
    LX_KEY_L,
    LX_KEY_M,
    LX_KEY_N,
    LX_KEY_O,
    LX_KEY_P,
    LX_KEY_Q,
    LX_KEY_R,
    LX_KEY_S,
    LX_KEY_T,
    LX_KEY_U,
    LX_KEY_V,
    LX_KEY_W,
    LX_KEY_X,
    LX_KEY_Y,
    LX_KEY_Z,
    
    // numbers
    LX_KEY_0,
    LX_KEY_1,
    LX_KEY_2,
    LX_KEY_3,
    LX_KEY_4,
    LX_KEY_5,
    LX_KEY_6,
    LX_KEY_7,
    LX_KEY_8,
    LX_KEY_9,

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

    // special
    LX_KEY_BACKSPACE,
    LX_KEY_ENTER,
    LX_KEY_RSHIFT,
    LX_KEY_RCTRL,
    LX_KEY_RALT,
    LX_KEY_LALT,
    LX_KEY_LCTRL,
    LX_KEY_LSHIFT,
    LX_KEY_CAPSLOCK,
    LX_KEY_TAB,
    LX_KEY_ESCAPE,

    // function keys
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

    // arrow keys
    LX_KEY_UP,
    LX_KEY_DOWN,
    LX_KEY_RIGHT,
    LX_KEY_LEFT,

    LX_KEY_LAST
}
lx_kb_key;

typedef enum _lx_ms_button
{
    // standard
    LX_MS_LEFT,
    LX_MS_RIGHT,
    LX_MS_MIDDLE,

    LX_MS_LAST
}
lx_ms_button;

typedef struct _lx_ms_position
{
    double x;
    double y;
}
lx_ms_position;

//
//  querying
//

/**
 * @brief Queries if a certain key is currently being held down.
 *
 * @param key The key to query.
 *
 * @return 1 for true, 0 for false.
 */
int lx_key_is_down(lx_kb_key key);

/**
 * @brief Queries if a certain key was pressed. This works similarly to
 * `lx_key_is_down`, except it only returns true once until the key is released
 * and re-pressed.
 *
 * @param key The key to query.
 *
 * @return 1 for true, 0 for false.
 */
int lx_key_was_down(lx_kb_key key);

/**
 * @brief Queries if a certain mouse button is currently being held down.
 *
 * @param button The button to query.
 * 
 * @return 1 for true, 0 for false.
 */
int lx_mouse_is_down(lx_ms_button button);

/**
 * @brief Queries if a certain mouse button was pressed. This works similarly
 * to `lx_mouse_is_down`, except it only returns true once until the button is
 * released and re-pressed.
 *
 * @param button The button to query.
 * 
 * @return 1 for true, 0 for false.
 */
int lx_mouse_was_down(lx_ms_button button);

/**
 * @brief Queries the current location of the mouse on the window.
 *
 * @return A position struct with the x and y values of the mouse position. If
 * the mouse is not in the window, the last know position is returned instead.
 */
lx_ms_position lx_mouse_get_pos();

LX_END_HEADER
