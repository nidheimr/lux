#pragma once

#include "lux/core.h"

// types
// ---------------------------------------------------------------- 

typedef struct _window_store window_store;

typedef struct _global_store
{
    int alive;
    int gl_version;

    window_store* window;
}
global_store;

// lifetime
// ---------------------------------------------------------------- 

extern lx_init_props lt_props;
extern global_store* lt_store;

// window
// ----------------------------------------------------------------

// creates a window with the given parameters
int window_create();

// destroys a window completely
void window_destroy();

// polls window input events
void window_poll_events();

// swaps window front and back buffers
void window_swap_buffers();

// gets the time since the window was created
double window_get_time();

// gets the predicted fps of the window
double window_get_fps();

// gets the delta time between frames
double window_get_delta();
