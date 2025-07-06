#include "lux/input.h"

#include "codes.h"

#include <stdint.h>

//
//  private
//

static uint8_t states[512] = { 0 }; // 512 is arbitrary, its above the highest code in codes.h
static double pos[2] = { 0 };

void inp_update_key(uint32_t key, uint32_t state)
{
    if (key > 512) return;
    states[key] = state;
}

void inp_update_mouse_button(uint32_t btn, uint32_t state)
{
    if (btn > 512) return;
    states[btn] = state;
}

void inp_update_mouse_pos(double x, double y)
{
    pos[0] = x;
    pos[1] = y;
}

int inp_is_down(int code)
{
    if (states[code] == 1)
        states[code] = 2;
    
    return states[code] >= 1 ? 1 : 0;
}

int inp_was_down(int code)
{
    int was = states[code] == 1 ? 1 : 0;
    if (states[code] == 1)
        states[code] = 2;

    return was; 
}

//
//  public
//

int lx_key_is_down(lx_kb_key key)
{
    int code = get_code_from_key(key);
    if (code == -1) return 0;

    return inp_is_down(code);
}

int lx_key_was_down(lx_kb_key key)
{
    int code = get_code_from_key(key);
    if (code == -1) return 0;

    return inp_was_down(code);
}

int lx_mouse_is_down(lx_ms_button button)
{
    int code = get_code_from_button(button);
    if (code == -1) return 0;

    return inp_is_down(code);
}

int lx_mouse_was_down(lx_ms_button button)
{
    int code = get_code_from_button(button);
    if (code == -1) return 0;

    return inp_was_down(code);
}

lx_ms_position lx_mouse_get_pos()
{
    return (lx_ms_position){ .x = pos[0], .y = pos[1] };
}
