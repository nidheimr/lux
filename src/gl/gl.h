#pragma once

// loader
// ----------------------------------------------------------------

// load the highest support opengl version functions, leaving the rest as NULL
int gl_load();

// unload all opengl functions, setting them to NULL so they cannot be used
void gl_unload();

// returns 1 if gl functions have been loaded, 0 otherwise
int gl_is_loaded();
