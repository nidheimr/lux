#pragma once

#include "external.h"
LX_BEGIN_HEADER

//
//  window
//

typedef struct _lx_window lx_window;

typedef void (*lx_window_resize_callback)(lx_window* window, int width, int height);

typedef void (*lx_error_callback)(const char* err);
typedef void (*lx_debug_callback)(const char* dbg);

typedef struct _lx_window_properties
{
    const char* title;
    int width;
    int height;

    lx_window_resize_callback on_resize;

    lx_error_callback on_error;
    lx_debug_callback on_debug;
}
lx_window_properties;

/**
 * @brief Creates a window with the specified properties.
 * 
 * The caller is responsible for destroying the window with `lx_window_destroy`
 * when they are done with it.
 * 
 * @param properties A window properties structure. 
 *
 * @return A pointer to the window.
 */
lx_window* lx_window_create(lx_window_properties properties);

/**
 * @brief Properly closes the window and frees any memory associated with it. The
 * window cannot be used after calling this.
 *
 * @param window The window pointer.
 */
void lx_window_destroy(lx_window* window);

/**
 * @brief Returns the current title associated with the window.
 *
 * @param window The window pointer.
 *
 * @return The window title.
 */
const char* lx_window_get_title(lx_window* window);

/**
 * @brief Returns the current width associated with the window.
 *
 * @param window The window pointer.
 *
 * @return The window width.
 */
int lx_window_get_width(lx_window* window);

/**
 * @brief Returns the current height associated with the window.
 *
 * @param window The window pointer.
 *
 * @return The window height.
 */
int lx_window_get_height(lx_window* window);

/**
 * @brief Returns the time since the last frame and the current.
 *
 * @param window The window pointer.
 *
 * @return Delta time in milliseconds.
 */
double lx_window_get_delta_time(lx_window* window);

/**
 * @brief Returns the amount of frames rendered in a second. Note that this is
 * predicted, not actually measured, so assume some inaccuracy.
 *
 * @param window The window pointer.
 *
 * @return A predicted amount of frames rendered in the last second.
 */
int lx_window_get_fps(lx_window* window);

/**
 * @brief Return the precise amount of time since the windows creation. 
 *
 * @param window The window pointer.
 *
 * @return Time elapsed in seconds.
 */
double lx_window_get_time_elapsed(lx_window* window);

/**
 * @brief Polls the window events and processes any input received. then proceeds
 * to clear the back buffer ready for drawing.
 *
 * Though not required, it is recommended to call this function **before** a
 * call to `lx_window_swap_buffers`.
 *
 * @param window The window pointer.
 */
void lx_window_update(lx_window* window);

/**
 * @brief Swaps the front and back buffers of the window, presenting whatever was
 * drawn on the back buffer. 
 *
 * Though not required, it is recommended to call this function **after** a
 * call to `lx_window_update`.
 *
 * @param window The window pointer.
 */
void lx_window_swap_buffers(lx_window* window);

/**
 * @brief Used to detect if a quit signal has been given to the window either through
 * the user trying to close the window or through signals.
 *
 * @param window The window pointer.
 *
 * @return The status of the window. 1 means the window is alive and okay, 0
 * means that a quit signal has been received and the window should terminate.
 */
int lx_window_is_alive(lx_window* window);

//
//  shader
//

typedef struct _lx_shader_properties
{
    const char* vertex_file;
    const char* fragment_file; 
}
lx_shader_properties;

/**
 * @brief Create a shader program directly from vertex and fragment shader
 * files.
 *
 * The caller is responsible for destroying the shader with `lx_shader_destroy`
 * when they are done with it.
 *
 * It is important to note that this is merely a convenience function. You are
 * still responsible for everything on the OpenGL side.
 *
 * @param properties A shader properties structure. 
 *
 * @return The shader program created with the given vertex and fragment
 * sources.
 */
unsigned int lx_shader_create(lx_shader_properties properties);

/**
 * @brief Properly destroys the shader and frees any memory associated with it.
 * The shader cannot be used after calling this.
 *
 * It is important to note that this is merely a convenience function. You are
 * still responsible for everything on the OpenGL side.
 *
 * @param shader The shader.
 */
void lx_shader_destroy(unsigned int shader);

LX_END_HEADER
