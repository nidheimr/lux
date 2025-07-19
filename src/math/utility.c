#include "lux/math.h"

#include <math.h>

// private source
// ----------------------------------------------------------------

static const float PI = 3.14159265358979323846;

// public header
// ----------------------------------------------------------------

float lx_float_clamp(float f, float min, float max)
{
    if (f < min) return min;
    if (f > max) return max;
    return f;
}

float lx_float_lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

int lx_float_equal(float a, float b, float epsilon)
{
    return fabsf(a - b) <= epsilon;
}

float lx_deg_to_rad(float degrees)
{
    return degrees * (PI / 180); 
}

float lx_rad_to_deg(float radians)
{
    return radians * (180 / PI);
}
