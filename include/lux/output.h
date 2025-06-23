#pragma once

#include "external.h"
LX_BEGIN_HEADER

//
//  window
//

/**
 * @brief Creates a window with the specified properties.
 * 
 * The caller is responsible for destroying the window with `lx_window_destroy`
 * when they are done with it.
 * 
 * @param title The title of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 */
void lx_window_create(const char* title, int width, int height);

/**
 * @brief Properly closes the window and frees any memory associated with it. The
 * window cannot be used after calling this.
 */
void lx_window_destroy();

/**
 * @brief Polls the window events and processes any input received. then proceeds
 * to clear the back buffer ready for drawing.
 *
 * Though not required, it is recommended to call this function **before** a
 * call to `lx_window_render`.
 */
void lx_window_update();

/**
 * @brief Swaps the front and back buffers of the window, presenting whatever was
 * drawn on the back buffer. 
 *
 * Though not required, it is recommended to call this function **after** a
 * call to `lx_window_update`.
 */
void lx_window_render();

/**
 * @brief Used to detect if a quit signal has been given to the window either through
 * the user trying to close the window or through signals.
 *
 * @return The status of the window. 1 means the window is alive and okay, 0
 * means that a quit signal has been received and the window should terminate.
 */
int lx_window_is_alive();

//
//  shader
//

typedef unsigned int lx_shader;

/**
 * @brief Create a shader program directly from vertex and fragment shader
 * files.
 *
 * The caller is responsible for destroying the shader with `lx_shader_destroy`
 * when they are done with it.
 *
 * @param vertex_file The file containing the vertex source code.
 * @param fragment_file The file containing the fragment source code.
 *
 * @return The ID of the shader, compatible with OpenGL functions, or 0 on
 * failure.
 */
lx_shader lx_shader_create(const char* vertex_file, const char* fragment_file);

/**
 * @brief Properly destroys the shader and frees any memory associated with it.
 * The shader cannot be used after calling this.
 *
 * @param shader The shader ID.
 */
void lx_shader_destroy(lx_shader shader);

/**
 * @brief Sets the given shader as the active one, all future rendering
 * functions will use this shader until specified otherwise.
 *
 * @param shader The shader ID.
 */
void lx_shader_use(lx_shader shader);

/**
 * @brief Draws a triangle on the screen. This shouldnt be used for actual
 * rendering, it is mainly a utility to test shaders or test that a window
 * was setup correctly.
 *
 * @param shader The shader ID.
 */
void lx_shader_test(lx_shader shader);

LX_END_HEADER
