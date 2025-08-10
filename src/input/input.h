#pragma once

#include "lux/input.h"

// tracking
// ---------------------------------------------------------------- 

// change the state of a key stored in the tracker
void change_key_state(lx_keycode key, lx_keystate state);

// get the state of a key according to the tracker
lx_keystate get_key_state(lx_keycode key);

// update the location of the mouse pointer
void update_mouse_position(double x, double y);

// get the location of the mouse pointer
lx_mousepos get_mouse_position();

// update mouse scroll amount
void update_mouse_scroll(double scroll);

// get mouse scroll amount
double get_mouse_scroll();

// translation
// ---------------------------------------------------------------- 

// translates a platform specific code to a key enum
lx_keycode code_to_key(int code);
