#pragma once

#include "api.h"
LX_BEGIN_HEADER

#include "input.h"

// types
// ----------------------------------------------------------------

typedef void (*lx_on_resize)(int width, int height);
typedef void (*lx_on_error)(const char* desc);
typedef void (*lx_on_key_event)(lx_keycode key, lx_keystate state);

typedef struct _lx_init_props
{
    const char* title;
    int width;
    int height;

    lx_on_key_event on_key_event;
    lx_on_resize on_resize;
    lx_on_error on_error;
}
lx_init_props;

// lifetime
// ----------------------------------------------------------------

/**
 * @brief Initialises Lux and creates a window using the provided properties,
 * loading an OpenGL context for use.
 *
 * Most other Lux functions cannot be used without first calling this.
 *
 * @param props The properties structure.
 *
 * @return 0 if Lux initialised correctly, 1 otherwise.
 */
LX_API int lx_init(lx_init_props props);

/**
 * @brief Terminates Lux and destroys the active window, freeing all associated
 * memory.
 *
 * Most other Lux functions cannot be used after calling this.
 */
LX_API void lx_quit();

/**
 * @brief Queries if Lux is currently classed as alive, meaning that things
 * should continue as normal.
 *
 * @return 1 if alive, 0 otherwise.
 */
LX_API int lx_is_alive();

/**
 * @brief Returns the major and minor version of the OpenGL context that was
 * created with initialisation.
 *
 * @return The OpenGL version.
 */
LX_API double lx_get_loaded_gl_version();

// management
// ----------------------------------------------------------------

/**
 * @brief Processes any pending events from the window, passing them along to
 * the appropriate internal system or associated callback.
 */
LX_API void lx_poll_events();

/**
 * @brief Swaps the front and back buffers of the active window, essentially
 * showing all of the rendering done since the last call to this function.
 */
LX_API void lx_swap_buffers();

/**
 * @brief Predicts the total amount of frames that will be complete per second.
 *
 * @return The frames per second.
 */
LX_API double lx_get_fps();

/**
 * @brief Calculates the time it took to complete the last frame.
 *
 * @return The delta time.
 */
LX_API double lx_get_delta();

/**
 * @brief Returns the amount of time that has elapsed since Lux initialisation.
 * This resets if Lux has been quit then reinitialised.
 *
 * @return The time elapsed in seconds.
 */
LX_API double lx_get_time();

/**
 * @brief Returns the current width of the window.
 *
 * @return The window width.
 */
LX_API int lx_get_width();

/**
 * @brief Returns the current height of the window.
 *
 * @return The window height.
 */
LX_API int lx_get_height();

LX_END_HEADER
