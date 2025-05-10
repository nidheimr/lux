#pragma once

//
//  window
//

typedef struct _lx_window lx_window;

/**
 * @brief Creates a window with the specified properties.
 * 
 * The caller is responsible for destroying the window with `lx_window_destroy`
 * when they are done with it.
 * 
 * @param title The title of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 *
 * @return The pointer to the window.
 */
lx_window* lx_window_create(const char* title, int width, int height);

/**
 * Properly closes the window and frees any memory associated with it. The
 * window cannot be used after calling this.
 *
 * @param window The pointer to the window.
 */
void lx_window_destroy(lx_window* window);

/**
 * Polls the window events and processes any input received. then proceeds
 * to clear the back buffer ready for drawing.
 *
 * Though not required, it is recommended to call this function **before** a
 * call to `lx_window_render`.
 *
 * @param window The pointer to the window.
 */
void lx_window_update(lx_window* window);

/**
 * Swaps the front and back buffers of the window, presenting whatever was
 * drawn on the back buffer. 
 *
 * Though not required, it is recommended to call this function **after** a
 * call to `lx_window_update`.
 *
 * @param window The pointer to the window.
 */
void lx_window_render(lx_window* window);

/**
 * Used to detect if a quit signal has been given to the window either through
 * the user trying to close the window or through signals.
 *
 * @param window The pointer to the window.
 *
 * @return The status of the window. 1 means the window is alive and okay, 0
 * means that a quit signal has been received and the window should terminate.
 */
int lx_window_is_alive(lx_window* window);
