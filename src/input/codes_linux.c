#include "lux/input.h"

int get_code_from_key(lx_kb_key key)
{
    switch (key)
    {
        case LX_KEY_A: return 30;
        case LX_KEY_B: return 48;
        case LX_KEY_C: return 46;
        case LX_KEY_D: return 32;
        case LX_KEY_E: return 18;
        case LX_KEY_F: return 33;
        case LX_KEY_G: return 34;
        case LX_KEY_H: return 35;
        case LX_KEY_I: return 20;
        case LX_KEY_J: return 36;
        case LX_KEY_K: return 37;
        case LX_KEY_L: return 38;
        case LX_KEY_M: return 50;
        case LX_KEY_N: return 49;
        case LX_KEY_O: return 24;
        case LX_KEY_P: return 25;
        case LX_KEY_Q: return 16;
        case LX_KEY_R: return 19;
        case LX_KEY_S: return 31;
        case LX_KEY_T: return 20;
        case LX_KEY_U: return 22;
        case LX_KEY_V: return 47;
        case LX_KEY_W: return 17;
        case LX_KEY_X: return 45;
        case LX_KEY_Y: return 21;
        case LX_KEY_Z: return 44;
        case LX_KEY_0: return 11;
        case LX_KEY_1: return 2;
        case LX_KEY_2: return 3;
        case LX_KEY_3: return 4;
        case LX_KEY_4: return 5;
        case LX_KEY_5: return 6;
        case LX_KEY_6: return 7;
        case LX_KEY_7: return 8;
        case LX_KEY_8: return 9;
        case LX_KEY_9: return 10;
        case LX_KEY_MINUS: return 12;
        case LX_KEY_EQUAL: return 13;
        case LX_KEY_LEFTBRACE: return 26;
        case LX_KEY_RIGHTBRACE: return 27;
        case LX_KEY_SEMICOLON: return 39;
        case LX_KEY_APOSTROPHE: return 40;
        case LX_KEY_GRAVE: return 41;
        case LX_KEY_BACKSLASH: return 43;
        case LX_KEY_COMMA: return 51;
        case LX_KEY_DOT: return 52;
        case LX_KEY_SLASH: return 53;
        case LX_KEY_BACKSPACE: return 14;
        case LX_KEY_ENTER: return 28;
        case LX_KEY_RSHIFT: return 54;
        case LX_KEY_RCTRL: return 97;
        case LX_KEY_RALT: return 100;
        case LX_KEY_LALT: return 56;
        case LX_KEY_LCTRL: return 29;
        case LX_KEY_LSHIFT: return 42;
        case LX_KEY_CAPSLOCK: return 58;
        case LX_KEY_TAB: return 15;
        case LX_KEY_ESCAPE: return 1;
        case LX_KEY_F1: return 59;
        case LX_KEY_F2: return 60;
        case LX_KEY_F3: return 61;
        case LX_KEY_F4: return 62;
        case LX_KEY_F5: return 63;
        case LX_KEY_F6: return 64;
        case LX_KEY_F7: return 65;
        case LX_KEY_F8: return 66;
        case LX_KEY_F9: return 67;
        case LX_KEY_F10: return 68;
        case LX_KEY_F11: return 87;
        case LX_KEY_F12: return 88;
        case LX_KEY_UP: return 103;
        case LX_KEY_DOWN: return 108;
        case LX_KEY_RIGHT: return 106;
        case LX_KEY_LEFT: return 105;
        default: return -1;
    }
}

int get_code_from_button(lx_ms_button btn)
{
    switch (btn)
    {
        case LX_MS_LEFT: return 272;
        case LX_MS_RIGHT: return 273;
        case LX_MS_MIDDLE: return 274;
        default: return -1;
    }
}
