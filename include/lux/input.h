#pragma once

#include "external.h"
LX_BEGIN_HEADER

#include "codes.h"

//
//  querying
//

typedef struct _lx_ms_position
{
    double x;
    double y;
}
lx_ms_position;

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
 * @brief Queries if the mouse was scrolled in the last update and if so, by
 * how much.
 *
 * @return Positive implies the wheel was scrolled up, negative implies the
 * opposite. 0 implies no scroll at all.
 */
double lx_mouse_get_scroll();

/**
 * @brief Queries the current location of the mouse on the window.
 *
 * @return A position struct with the x and y values of the mouse position. If
 * the mouse is not in the window, the last know position is returned instead.
 */
lx_ms_position lx_mouse_get_pos();

LX_END_HEADER
