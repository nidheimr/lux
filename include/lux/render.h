#pragma once

//
//  window
//

typedef struct _lx_window lx_window;

lx_window* lx_window_new(const char* title, int width, int height);
void lx_window_delete(lx_window* window);

void lx_window_update(lx_window* window);
void lx_window_render(lx_window* window);

int lx_window_has_received_quit_signal(lx_window* window);

//
//  shader
//

typedef unsigned int lx_shader;

lx_shader lx_shader_new(const char* vertex_file, const char* fragment_file);
void lx_shader_delete(lx_shader shader);

void lx_shader_use(lx_shader shader);